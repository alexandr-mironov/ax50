#!/bin/bash
#
# ax50-restore.sh — восстановление прошивки AX50 из резервной копии
#
# Восстанавливает MTD-разделы из бэкапа, созданного ax50-backup.sh.
# ВНИМАНИЕ: Восстановление U-Boot может окирпичить роутер!
#
# Использование:
#   ./scripts/ax50-restore.sh [backup_dir] [user@host]
#
# Примеры:
#   ./scripts/ax50-restore.sh ./backups/ax50-20260413-120000
#   ./scripts/ax50-restore.sh ./backups/ax50-20260413-120000 root@192.168.1.1
#
set -euo pipefail

BACKUP_DIR="${1:?Использование: $0 <backup_dir> [user@host]}"
ROUTER="${2:-root@192.168.1.1}"
SSH_OPTS="-o StrictHostKeyChecking=no -o ConnectTimeout=10"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

info()  { echo -e "${GREEN}[INFO]${NC} $*"; }
warn()  { echo -e "${YELLOW}[WARN]${NC} $*"; }
error() { echo -e "${RED}[ERROR]${NC} $*"; exit 1; }

[ -d "$BACKUP_DIR" ] || error "Каталог бэкапа не найден: $BACKUP_DIR"
[ -f "$BACKUP_DIR/mtd-table.txt" ] || error "Файл mtd-table.txt не найден в бэкапе"

echo ""
echo "========================================="
echo " AX50 Firmware Restore"
echo "========================================="
echo " Бэкап:  $BACKUP_DIR"
echo " Роутер: $ROUTER"
echo "========================================="
echo ""

# --- Проверка бэкапа ---
info "Проверка контрольных сумм..."
if [ -f "$BACKUP_DIR/sha256sums.txt" ]; then
    (cd "$BACKUP_DIR" && sha256sum -c sha256sums.txt) || error "Контрольные суммы не совпадают!"
    info "Контрольные суммы OK"
else
    warn "Файл sha256sums.txt не найден, пропуск проверки"
fi

# --- Список доступных разделов ---
echo ""
info "Доступные образы для восстановления:"
echo ""

# Разделы, безопасные для восстановления
SAFE_PARTS="system_sw calibration gphyfirmware ubootconfigA ubootconfigB res"
# Опасные разделы (U-Boot)
DANGER_PARTS="uboot"

for f in "$BACKUP_DIR"/mtd*-*.bin; do
    [ -f "$f" ] || continue
    name=$(basename "$f" .bin | sed 's/mtd[0-9]*-//')
    size=$(stat -c%s "$f")
    size_mb=$(echo "scale=1; $size / 1048576" | bc)

    if echo "$DANGER_PARTS" | grep -qw "$name"; then
        echo -e "  ${RED}[ОПАСНО]${NC} $(basename $f) (${size_mb}MB) — U-Boot, восстановление может окирпичить!"
    elif echo "$SAFE_PARTS" | grep -qw "$name"; then
        echo -e "  ${GREEN}[OK]${NC}     $(basename $f) (${size_mb}MB)"
    else
        echo -e "  ${YELLOW}[?]${NC}      $(basename $f) (${size_mb}MB)"
    fi
done

echo ""

# --- Подключение ---
info "Проверка SSH-подключения..."
ssh $SSH_OPTS "$ROUTER" "echo ok" >/dev/null 2>&1 \
    || error "Не удалось подключиться к $ROUTER"

# --- Выбор разделов ---
echo ""
warn "Какие разделы восстановить?"
echo ""
echo "  1) Только system_sw (ядро + rootfs) — РЕКОМЕНДУЕТСЯ"
echo "  2) Все разделы КРОМЕ U-Boot — безопасно"
echo "  3) ВСЕ разделы включая U-Boot — ОПАСНО"
echo "  4) Отмена"
echo ""
read -p "Выбор (1-4): " choice

case "$choice" in
    1) PARTS="system_sw" ;;
    2) PARTS="$SAFE_PARTS" ;;
    3)
        warn "ВНИМАНИЕ: Восстановление U-Boot может ОКИРПИЧИТЬ роутер!"
        warn "Продолжайте только если уверены и имеете UART-доступ."
        read -p "Введите 'I UNDERSTAND' для продолжения: " confirm
        [ "$confirm" = "I UNDERSTAND" ] || { info "Отменено."; exit 0; }
        PARTS="$DANGER_PARTS $SAFE_PARTS"
        ;;
    *) info "Отменено."; exit 0 ;;
esac

# --- Восстановление ---
echo ""
warn "========================================="
warn " Сейчас будут записаны следующие разделы:"
for p in $PARTS; do
    echo "   - $p"
done
warn " НЕ ОТКЛЮЧАЙТЕ ПИТАНИЕ!"
warn "========================================="
echo ""
read -p "Начать восстановление? (yes/NO): " confirm
[ "$confirm" = "yes" ] || { info "Отменено."; exit 0; }

for part_name in $PARTS; do
    # Находим файл бэкапа
    backup_file=$(ls "$BACKUP_DIR"/mtd*-${part_name}.bin 2>/dev/null | head -1)
    [ -f "$backup_file" ] || { warn "Бэкап $part_name не найден, пропуск"; continue; }

    # Находим MTD-устройство на роутере
    mtd_dev=$(ssh $SSH_OPTS "$ROUTER" "grep '\"$part_name\"' /proc/mtd | cut -d: -f1")
    [ -n "$mtd_dev" ] || { warn "Раздел $part_name не найден на роутере, пропуск"; continue; }

    size=$(stat -c%s "$backup_file")
    size_mb=$(echo "scale=1; $size / 1048576" | bc)

    info "Восстановление $part_name → /dev/$mtd_dev (${size_mb}MB)..."

    # Загрузка и запись
    ssh $SSH_OPTS "$ROUTER" "cat > /tmp/restore-$part_name.bin" < "$backup_file"

    # Проверка MD5
    local_md5=$(md5sum "$backup_file" | cut -d' ' -f1)
    remote_md5=$(ssh $SSH_OPTS "$ROUTER" "md5sum /tmp/restore-$part_name.bin | cut -d' ' -f1")
    if [ "$local_md5" != "$remote_md5" ]; then
        error "MD5 не совпадает для $part_name! Прерывание."
    fi

    # Запись через mtd write или nandwrite
    ssh $SSH_OPTS "$ROUTER" "
        if command -v nandwrite >/dev/null 2>&1; then
            flash_erase /dev/$mtd_dev 0 0 && \
            nandwrite -p /dev/$mtd_dev /tmp/restore-$part_name.bin
        elif command -v mtd >/dev/null 2>&1; then
            mtd write /tmp/restore-$part_name.bin $part_name
        else
            echo 'ERROR: нет mtd/nandwrite утилит!'
            exit 1
        fi
        rm -f /tmp/restore-$part_name.bin
    " || { error "Ошибка записи $part_name!"; }

    info "  $part_name — OK"
done

echo ""
info "========================================="
info "Восстановление завершено!"
info "========================================="
echo ""
read -p "Перезагрузить роутер? (y/N): " reboot
if [ "$reboot" = "y" ]; then
    ssh $SSH_OPTS "$ROUTER" "reboot" 2>/dev/null || true
    info "Роутер перезагружается..."
fi
