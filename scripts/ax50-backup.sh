#!/bin/bash
#
# ax50-backup.sh — создание полной резервной копии прошивки AX50
#
# Подключается к роутеру по SSH, дампит все MTD-разделы и UBI-тома.
# Результат: каталог с образами разделов + metadata.
#
# Использование:
#   ./scripts/ax50-backup.sh [user@host] [backup_dir]
#
# Примеры:
#   ./scripts/ax50-backup.sh root@192.168.1.1
#   ./scripts/ax50-backup.sh root@192.168.1.1 ./backups/my-ax50
#
set -euo pipefail

ROUTER="${1:-root@192.168.1.1}"
BACKUP_DIR="${2:-./backups/ax50-$(date +%Y%m%d-%H%M%S)}"
SSH_OPTS="-o StrictHostKeyChecking=no -o ConnectTimeout=10"

# Цвета
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

info()  { echo -e "${GREEN}[INFO]${NC} $*"; }
warn()  { echo -e "${YELLOW}[WARN]${NC} $*"; }
error() { echo -e "${RED}[ERROR]${NC} $*"; exit 1; }

# --- Проверки ---
info "Проверка подключения к $ROUTER..."
ssh $SSH_OPTS "$ROUTER" "echo ok" >/dev/null 2>&1 \
    || error "Не удалось подключиться к $ROUTER по SSH.
  Убедитесь что:
  1. Роутер доступен по сети
  2. SSH включён (порт 22)
  3. Учётные данные верны
  Попробуйте: ssh $ROUTER"

mkdir -p "$BACKUP_DIR"
info "Каталог бэкапа: $BACKUP_DIR"

# --- Сбор информации ---
info "Сбор информации о системе..."
ssh $SSH_OPTS "$ROUTER" "
    echo '=== SYSTEM ==='
    cat /etc/openwrt_release 2>/dev/null || echo 'no openwrt_release'
    echo '=== BOARD ==='
    cat /tmp/sysinfo/board_name 2>/dev/null || echo 'unknown'
    echo '=== MODEL ==='
    cat /tmp/sysinfo/model 2>/dev/null || echo 'unknown'
    echo '=== KERNEL ==='
    uname -a
    echo '=== UPTIME ==='
    uptime
    echo '=== CMDLINE ==='
    cat /proc/cmdline
" > "$BACKUP_DIR/system-info.txt" 2>&1
info "Информация о системе сохранена"

# --- Таблица MTD-разделов ---
info "Чтение таблицы MTD-разделов..."
ssh $SSH_OPTS "$ROUTER" "cat /proc/mtd" > "$BACKUP_DIR/mtd-table.txt"
cat "$BACKUP_DIR/mtd-table.txt"

# --- Таблица UBI ---
info "Чтение UBI-информации..."
ssh $SSH_OPTS "$ROUTER" "
    echo '=== UBI devices ==='
    ls -la /dev/ubi* 2>/dev/null || echo 'no UBI devices'
    echo '=== UBI volumes ==='
    if [ -d /sys/class/ubi ]; then
        for d in /sys/class/ubi/ubi*_*; do
            [ -d \"\$d\" ] || continue
            name=\$(cat \"\$d/name\" 2>/dev/null)
            size=\$(cat \"\$d/data_bytes\" 2>/dev/null)
            type=\$(cat \"\$d/type\" 2>/dev/null)
            echo \"\$(basename \$d): name=\$name size=\$size type=\$type\"
        done
    fi
    echo '=== Mount points ==='
    mount | grep -E 'ubi|mtd|jffs|squash'
" > "$BACKUP_DIR/ubi-info.txt" 2>&1
cat "$BACKUP_DIR/ubi-info.txt"

# --- Дамп MTD-разделов ---
info "Дамп MTD-разделов (это может занять несколько минут)..."

# Считываем список разделов
MTD_LIST=$(ssh $SSH_OPTS "$ROUTER" "cat /proc/mtd" | grep "^mtd" | sed 's/://')

echo "$MTD_LIST" | while read mtd size erasesize name; do
    # Убираем кавычки из имени
    name=$(echo "$name" | tr -d '"')
    dev="/dev/$mtd"

    # Размер в байтах
    size_dec=$((16#$size))
    size_mb=$(echo "scale=1; $size_dec / 1048576" | bc)

    info "  Дамп $dev ($name, ${size_mb}MB)..."

    # Для маленьких разделов (< 2MB) — dd напрямую
    # Для больших — nanddump если доступен (корректнее для NAND)
    ssh $SSH_OPTS "$ROUTER" "
        if command -v nanddump >/dev/null 2>&1; then
            nanddump -f /dev/stdout $dev 2>/dev/null
        else
            dd if=$dev bs=131072 2>/dev/null
        fi
    " > "$BACKUP_DIR/${mtd}-${name}.bin"

    actual_size=$(stat -c%s "$BACKUP_DIR/${mtd}-${name}.bin" 2>/dev/null || echo 0)
    info "    Сохранено: ${mtd}-${name}.bin ($(echo "scale=1; $actual_size / 1048576" | bc)MB)"
done

# --- Дамп UBI-томов (если есть) ---
info "Дамп UBI-томов..."
ssh $SSH_OPTS "$ROUTER" "
    if [ -d /sys/class/ubi ]; then
        for d in /sys/class/ubi/ubi*_*; do
            [ -d \"\$d\" ] || continue
            vol=\$(basename \$d)
            name=\$(cat \"\$d/name\" 2>/dev/null)
            echo \"\$vol \$name\"
        done
    fi
" 2>/dev/null | while read vol name; do
    [ -z "$vol" ] && continue
    info "  Дамп /dev/$vol ($name)..."
    ssh $SSH_OPTS "$ROUTER" "dd if=/dev/$vol bs=131072 2>/dev/null" \
        > "$BACKUP_DIR/${vol}-${name}.bin" 2>/dev/null || warn "  Не удалось: $vol"
done

# --- Конфигурация ---
info "Сохранение конфигурации..."
ssh $SSH_OPTS "$ROUTER" "
    sysupgrade -b /tmp/backup.tar.gz 2>/dev/null && cat /tmp/backup.tar.gz && rm -f /tmp/backup.tar.gz
" > "$BACKUP_DIR/config-backup.tar.gz" 2>/dev/null || warn "sysupgrade backup не поддерживается"

# Проверка размера (если 0 — удалить)
[ -f "$BACKUP_DIR/config-backup.tar.gz" ] && \
    [ ! -s "$BACKUP_DIR/config-backup.tar.gz" ] && \
    rm -f "$BACKUP_DIR/config-backup.tar.gz"

# --- Контрольные суммы ---
info "Вычисление контрольных сумм..."
(cd "$BACKUP_DIR" && md5sum *.bin *.txt 2>/dev/null > md5sums.txt)
(cd "$BACKUP_DIR" && sha256sum *.bin 2>/dev/null > sha256sums.txt)

# --- Итог ---
echo ""
info "========================================="
info "Бэкап завершён: $BACKUP_DIR"
info "========================================="
ls -lh "$BACKUP_DIR/"
echo ""
total_size=$(du -sh "$BACKUP_DIR" | cut -f1)
info "Общий размер: $total_size"
echo ""
warn "ВАЖНО: Сохраните этот каталог в надёжном месте!"
warn "Для восстановления из бэкапа используйте: ./scripts/ax50-restore.sh"
