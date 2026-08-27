#!/bin/bash
#
# ax50-flash.sh — прошивка AX50 собранным образом
#
# Поддерживает два режима:
#   1. SSH sysupgrade — через SSH на работающий роутер (безопасно)
#   2. TFTP recovery  — через U-Boot TFTP (если система не грузится)
#
# Использование:
#   ./scripts/ax50-flash.sh [--method ssh|tftp] [user@host] [image]
#
# Примеры:
#   ./scripts/ax50-flash.sh                          # SSH, образ по умолчанию
#   ./scripts/ax50-flash.sh --method tftp 192.168.1.1
#   ./scripts/ax50-flash.sh root@192.168.1.1 bin/lantiq/grx350_1600_opensrc_71_sample/fullimage.img
#
set -euo pipefail

METHOD="ssh"
ROUTER=""
IMAGE=""
SSH_OPTS="-o StrictHostKeyChecking=no -o ConnectTimeout=10"
TFTP_DIR="/tmp/ax50-tftp"

# Образ по умолчанию
DEFAULT_IMAGE="bin/lantiq/grx350_1600_opensrc_71_sample/fullimage.img"
DEFAULT_SQUASHFS="bin/lantiq/openwrt-lantiq-xrx500-easy350_anywan-squashfs.image"

# Цвета
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

info()  { echo -e "${GREEN}[INFO]${NC} $*"; }
warn()  { echo -e "${YELLOW}[WARN]${NC} $*"; }
error() { echo -e "${RED}[ERROR]${NC} $*"; exit 1; }
step()  { echo -e "${CYAN}[STEP]${NC} $*"; }

usage() {
    cat <<'USAGE'
Прошивка TP-Link Archer AX50 (Lantiq GRX350)

Использование:
  ./scripts/ax50-flash.sh [опции] [user@host] [image]

Опции:
  --method ssh    Прошивка через SSH sysupgrade (по умолчанию)
  --method tftp   Прошивка через TFTP recovery (U-Boot)
  --dry-run       Только проверки, не прошивать
  --no-backup     Не создавать бэкап перед прошивкой
  -h, --help      Показать справку

Примеры:
  ./scripts/ax50-flash.sh
  ./scripts/ax50-flash.sh root@192.168.1.1
  ./scripts/ax50-flash.sh --method tftp 192.168.1.1
  ./scripts/ax50-flash.sh --no-backup root@192.168.1.1 my-image.img
USAGE
    exit 0
}

DRY_RUN=0
NO_BACKUP=0

# --- Разбор аргументов ---
while [ $# -gt 0 ]; do
    case "$1" in
        --method)  METHOD="$2"; shift 2 ;;
        --dry-run) DRY_RUN=1; shift ;;
        --no-backup) NO_BACKUP=1; shift ;;
        -h|--help) usage ;;
        *)
            if [ -z "$ROUTER" ]; then
                ROUTER="$1"
            elif [ -z "$IMAGE" ]; then
                IMAGE="$1"
            fi
            shift ;;
    esac
done

# Дефолты
[ -z "$ROUTER" ] && ROUTER="root@192.168.1.1"
if [ -z "$IMAGE" ]; then
    if [ -f "$DEFAULT_IMAGE" ]; then
        IMAGE="$DEFAULT_IMAGE"
    elif [ -f "$DEFAULT_SQUASHFS" ]; then
        IMAGE="$DEFAULT_SQUASHFS"
    else
        error "Образ не найден. Сначала соберите прошивку:
  docker run --rm -v \$(pwd):/build ax50-build make -j\$(nproc) V=s"
    fi
fi

[ -f "$IMAGE" ] || error "Файл не найден: $IMAGE"

IMAGE_SIZE=$(stat -c%s "$IMAGE")
IMAGE_MB=$(echo "scale=1; $IMAGE_SIZE / 1048576" | bc)

echo ""
echo "========================================="
echo " AX50 Firmware Flash"
echo "========================================="
echo " Метод:  $METHOD"
echo " Роутер: $ROUTER"
echo " Образ:  $IMAGE ($IMAGE_MB MB)"
echo " Dry-run: $([ $DRY_RUN -eq 1 ] && echo 'да' || echo 'нет')"
echo "========================================="
echo ""

# --- Проверка образа ---
step "Проверка образа..."
file_type=$(file "$IMAGE")
echo "  Тип: $file_type"

if echo "$file_type" | grep -q "u-boot legacy uImage"; then
    info "Формат uImage — OK"
elif echo "$file_type" | grep -q "Squashfs"; then
    info "Формат SquashFS — OK"
else
    warn "Нестандартный формат образа. Продолжить?"
    read -p "  (y/N): " confirm
    [ "$confirm" = "y" ] || exit 1
fi

# Проверка архитектуры
if echo "$file_type" | grep -q "MIPS"; then
    info "Архитектура MIPS — OK"
else
    warn "В образе не обнаружена архитектура MIPS!"
fi

# ==========================================================================
# SSH метод
# ==========================================================================
flash_ssh() {
    step "Проверка SSH-подключения..."
    ssh $SSH_OPTS "$ROUTER" "echo ok" >/dev/null 2>&1 \
        || error "Не удалось подключиться к $ROUTER"

    # Проверяем что это правильный роутер
    info "Проверка целевого устройства..."
    remote_info=$(ssh $SSH_OPTS "$ROUTER" "
        cat /proc/cpuinfo | grep 'system type' | head -1
        echo 'MTD:'
        cat /proc/mtd | head -5
    " 2>/dev/null)
    echo "$remote_info"

    if ! echo "$remote_info" | grep -qi "lantiq\|grx\|xrx"; then
        warn "Устройство не выглядит как Lantiq/GRX роутер!"
        read -p "  Продолжить? (y/N): " confirm
        [ "$confirm" = "y" ] || exit 1
    fi

    # Бэкап
    if [ $NO_BACKUP -eq 0 ]; then
        step "Создание бэкапа перед прошивкой..."
        bash "$(dirname "$0")/ax50-backup.sh" "$ROUTER" \
            || warn "Бэкап не удался. Продолжить без бэкапа?"
        read -p "  Продолжить прошивку? (y/N): " confirm
        [ "$confirm" = "y" ] || exit 1
    fi

    if [ $DRY_RUN -eq 1 ]; then
        info "DRY-RUN: прошивка не выполнена"
        return
    fi

    # Проверка свободного места на роутере
    step "Проверка свободного места..."
    free_space=$(ssh $SSH_OPTS "$ROUTER" "df /tmp | tail -1 | awk '{print \$4}'")
    need_kb=$((IMAGE_SIZE / 1024 + 1024))
    info "  Свободно: ${free_space}KB, нужно: ${need_kb}KB"
    [ "$free_space" -lt "$need_kb" ] && error "Недостаточно места в /tmp"

    # Загрузка
    step "Загрузка образа на роутер..."
    scp $SSH_OPTS "$IMAGE" "$ROUTER:/tmp/firmware.img" \
        || error "Не удалось загрузить образ"

    # Проверка целостности
    step "Проверка целостности..."
    local_md5=$(md5sum "$IMAGE" | cut -d' ' -f1)
    remote_md5=$(ssh $SSH_OPTS "$ROUTER" "md5sum /tmp/firmware.img | cut -d' ' -f1")
    if [ "$local_md5" = "$remote_md5" ]; then
        info "MD5 совпадает: $local_md5"
    else
        error "MD5 не совпадает! Локальный: $local_md5, удалённый: $remote_md5"
    fi

    # Прошивка
    echo ""
    warn "========================================="
    warn " ВНИМАНИЕ: Сейчас будет выполнена прошивка!"
    warn " Роутер перезагрузится."
    warn " НЕ ОТКЛЮЧАЙТЕ ПИТАНИЕ!"
    warn "========================================="
    echo ""
    read -p "  Начать прошивку? (yes/NO): " confirm
    [ "$confirm" = "yes" ] || { info "Отменено."; exit 0; }

    step "Выполнение sysupgrade..."
    # -n = не сохранять конфигурацию (чистая установка)
    ssh $SSH_OPTS "$ROUTER" "sysupgrade -n /tmp/firmware.img" 2>&1 || true

    echo ""
    info "Команда отправлена. Роутер перезагружается."
    info "Подождите 2-3 минуты и попробуйте подключиться."
    info "  ssh $ROUTER"
}

# ==========================================================================
# TFTP метод (U-Boot recovery)
# ==========================================================================
flash_tftp() {
    # Для TFTP нужен только IP (не user@host)
    ROUTER_IP=$(echo "$ROUTER" | sed 's/.*@//')
    HOST_IP="${HOST_IP:-192.168.1.100}"

    echo ""
    step "Прошивка через TFTP recovery (U-Boot)"
    echo ""
    warn "Этот метод требует:"
    warn "  1. TFTP-сервер на этом компьютере"
    warn "  2. Подключение к роутеру по Ethernet"
    warn "  3. Доступ к серийной консоли (UART) роутера"
    echo ""

    # Проверка tftp
    if ! command -v in.tftpd >/dev/null 2>&1 && ! command -v atftpd >/dev/null 2>&1; then
        warn "TFTP-сервер не установлен. Установите:"
        echo "  sudo apt install atftpd"
    fi

    if [ $DRY_RUN -eq 1 ]; then
        info "DRY-RUN: дальнейшие шаги не выполнены"
    fi

    # Подготовка
    mkdir -p "$TFTP_DIR"
    cp "$IMAGE" "$TFTP_DIR/firmware.img"
    info "Образ скопирован в $TFTP_DIR/firmware.img"

    echo ""
    echo "========================================="
    echo " Инструкция для TFTP recovery:"
    echo "========================================="
    echo ""
    echo " 1. Настройте IP на компьютере: $HOST_IP/24"
    echo ""
    echo " 2. Запустите TFTP-сервер:"
    echo "    sudo atftpd --daemon --no-fork --basedir $TFTP_DIR"
    echo ""
    echo " 3. Подключите серийную консоль к роутеру (115200 8N1)"
    echo ""
    echo " 4. Включите роутер и прервите автозагрузку (нажмите любую клавишу)"
    echo ""
    echo " 5. В консоли U-Boot введите:"
    echo "    GRX500 # setenv ipaddr $ROUTER_IP"
    echo "    GRX500 # setenv serverip $HOST_IP"
    echo "    GRX500 # tftpboot 0xa0400000 firmware.img"
    echo "    GRX500 # run ubi_init"
    echo "    GRX500 # upgrade 0xa0400000 \\\$(filesize)"
    echo ""
    echo " 6. После завершения:"
    echo "    GRX500 # reset"
    echo ""
    echo "========================================="
    echo ""
    warn "НЕ ОТКЛЮЧАЙТЕ ПИТАНИЕ во время прошивки!"
}

# --- Запуск ---
case "$METHOD" in
    ssh)  flash_ssh ;;
    tftp) flash_tftp ;;
    *)    error "Неизвестный метод: $METHOD. Используйте: ssh или tftp" ;;
esac
