#!/bin/bash
set -e

echo "=== Raspberry Pi Pico W FreeRTOS – Setup STABILE ==="

# ============================================================
#  TAG STABILI (cambiami solo se proprio ti serve)
# ============================================================
PICO_SDK_TAG="1.5.1"
FREERTOS_TAG="V10.5.1"

# ============================================================
# 1. Cleanup submodules vecchi
# ============================================================
echo "[1/6] Pulizia submodules esistenti..."

git submodule deinit -f lib/pico-sdk 2>/dev/null || true
git rm -f lib/pico-sdk 2>/dev/null || true
rm -rf lib/pico-sdk

git submodule deinit -f lib/FreeRTOS-Kernel 2>/dev/null || true
git rm -f lib/FreeRTOS-Kernel 2>/dev/null || true
rm -rf lib/FreeRTOS-Kernel

mkdir -p lib

# ============================================================
# 2. Aggiunta submodules STABILI
# ============================================================
echo "[2/6] Download Pico SDK (tag stabile: $PICO_SDK_TAG)"
git submodule add -b $PICO_SDK_TAG https://github.com/raspberrypi/pico-sdk lib/pico-sdk

echo "[3/6] Download FreeRTOS Kernel (tag stabile: $FREERTOS_TAG)"
git submodule add -b $FREERTOS_TAG https://github.com/FreeRTOS/FreeRTOS-Kernel lib/FreeRTOS-Kernel

# ============================================================
# 3. Inizializzazione submodules ricorsiva
# ============================================================
echo "[4/6] Inizializzazione submodules ricorsiva..."
git submodule update --init --recursive

# ============================================================
# 4. Configurazione build
# ============================================================
echo "[5/6] Creazione cartella build/"
rm -rf build
mkdir build
cd build

echo "[6/6] Configurazione e compilazione..."
cmake .. -DPICO_BOARD=pico_w
make -j$(nproc)

echo "========================================================="
echo " ✔ Setup COMPLETATO senza errori!"
echo " ✔ Firmware generato in: build/src/PICO_FREERTOS.uf2"
echo "========================================================="

