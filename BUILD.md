# Сборка прошивки AX50 (OpenWrt 15.05_ltq / UGW 7.1.1)

## Требования

- Docker
- ~20 GB свободного места на диске
- ext4 файловая система (не NTFS/exFAT). В WSL используйте нативную ext4, не `/mnt/c`

## Быстрый старт

### 1. Собрать Docker-образ

```bash
docker build -t ax50-build .
```

Образ основан на Ubuntu 18.04 — единственное поддерживаемое окружение сборки.
Содержит GCC 7.5, Python 2.7, и все необходимые зависимости.

### 2. Запустить сборку

```bash
docker run --rm -v $(pwd):/build ax50-build make -j$(nproc) V=s 2>&1 | tee build.log
```

Первая полная сборка занимает ~30-60 минут в зависимости от CPU.

### 3. Результат

Собранные пакеты:
```
bin/lantiq/packages/base/*.ipk    # основные пакеты
bin/lantiq/                       # образ прошивки (если bootcore собрался)
```

## Повторная сборка

Для пересборки после изменений:

```bash
# Инкрементальная пересборка (быстро)
docker run --rm -v $(pwd):/build ax50-build make -j$(nproc) V=s

# Полная чистая пересборка
docker run --rm -v $(pwd):/build ax50-build sh -c "rm -rf build_dir staging_dir/host staging_dir/toolchain-* staging_dir/target-* bin tmp logs && make -j\$(nproc) V=s"
```

## Параметры железа

| Параметр | Значение |
|----------|----------|
| Роутер | TP-Link Archer AX50 v1 |
| CPU | Lantiq GRX350 (MIPS32r2, 1004Kc, 800MHz) |
| RAM | 256 MB |
| Flash | 128 MB |
| Target | `lantiq/xrx500/easy350_anywan` |
| Compiler flags | `-Os -pipe -mips32r2 -mtune=1004kc -msoft-float` |

## Структура SDK

```
.
├── Dockerfile              # окружение сборки (Ubuntu 18.04)
├── .config                 # конфигурация сборки (3200+ строк)
├── package/                # 222 пакета
├── toolchain/              # GCC 4.8-linaro для MIPS + uClibc 0.9.33.2
├── target/                 # целевая платформа lantiq/xrx500
├── tools/                  # host-утилиты (cmake, mkimage, etc.)
├── ugw/                    # Lantiq UGW feeds (частично в репо)
├── feeds/                  # симлинки на feed-каталоги
├── dl/                     # скачанные исходники (tarballs)
├── build_dir/              # [генерируется] рабочие каталоги сборки
├── staging_dir/            # [генерируется] sysroot и toolchain
└── bin/                    # [генерируется] собранные пакеты и образы
```

## Патчи для совместимости с современным хостом

SDK изначально рассчитан на Ubuntu 14.04. Для сборки на Ubuntu 18.04 (Docker)
добавлены следующие патчи:

| Файл | Проблема | Решение |
|------|----------|---------|
| `include/prereq-build.mk` | Проверка Python 2.7 (есть в Docker, но проверка была некорректной) | Закомментирована |
| `scripts/config/Makefile` | Флаг линковщика `-melf_i386` передавался компилятору | Убран |
| `tools/make-ext4fs/patches/001-fix-sysmacros.patch` | `major()`/`minor()` переехали в `sys/sysmacros.h` | Добавлен include |
| `tools/mkimage/patches/210-gcc6_7_compat.patch` | u-boot 2014 не знает GCC 6+ | Fallback на compiler-gcc5.h |
| `tools/mkimage/patches/220-disable-fit-signature.patch` | RSA API несовместим с OpenSSL 1.1 | Отключён CONFIG_FIT_SIGNATURE |
| `tools/pkg-config/Makefile` | glib `-Werror=format-nonliteral` | Добавлен `-Wno-error=format-nonliteral` |
| `tools/automake/patches/300-perl5.26-fix-unescaped-braces.patch` | Perl 5.26+ запрещает `{` без экранирования в regex | Экранирован `\{` |
| `toolchain/gcc/patches/4.8-linaro/230-fix-cfns-gperf-gcc6-compat.patch` | `cfns.gperf` несовместим с хостовым GCC 6+ | Добавлен `__gnu_inline__` атрибут |
| `include/prereq-build.mk` (openssl) | `openssl version` выдаёт "LibreSSL", а не "OpenSSL" | grep принимает оба |
| `target/linux/x86/image/Config.in` | Битый симлинк (3 уровня `../` вместо 4) | Исправлена глубина |
| `target/linux/lantiq/patches-3.10/9999-ppa-stub-*` | PPA символы отсутствуют без `CONFIG_LTQ_PPA` | Stub функции в ppp_generic.c |
| `ugw/.../ltq_bootcore_env_prepare.sh` | `ln -s` падает при повторном запуске | Заменён на `ln -sf` |
| `ugw/.../linux-atm/patches/004-*` | Хардкод `/usr/include/stdint.h` в linux-atm | `#include_next <stdint.h>` |
| `.config` | `ez-ipupdate` падает на `-Werror=format-security` | Отключён пакет |

## Важно

- **Не смешивайте** хостовую и Docker-сборку. Бинарники, собранные на хосте,
  несовместимы с glibc в Docker (и наоборот). При переключении всегда делайте
  полную очистку.

- **Фиды UGW**: часть фидов (`feeds_ugw`, `feeds_thirdparty`, `feed_voice_cpe`)
  отсутствует в репозитории. Пакеты из этих фидов не собираются.

- **Не смешивайте** Docker-сборку с хостовой. `scripts/config/conf` и другие
  бинарники привязаны к glibc версии. При переключении — полная очистка.

## Устранение проблем

### Сборка падает внутри Docker
```bash
# Посмотреть последнюю ошибку:
grep "make\[2\]: \*\*\*" build.log | grep -v Waiting

# Пересобрать конкретный пакет:
docker run --rm -v $(pwd):/build ax50-build make package/имя_пакета/compile V=s
```

### Нужна чистая пересборка конкретного пакета
```bash
# Удалить build_dir пакета и пересобрать:
rm -rf build_dir/target-*/имя_пакета-*
docker run --rm -v $(pwd):/build ax50-build make package/имя_пакета/{clean,compile} V=s
```
