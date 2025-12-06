#!/bin/bash
set -e

echo "=== Raspberry Pi Pico W – Compilazione ==="

# ============================================================
# 1. Export PICO_SDK_PATH
# ============================================================
echo "[1/3] Imposto variabile PICO_SDK_PATH"
export PICO_SDK_PATH="$(pwd)/lib/pico-sdk"
echo "PICO_SDK_PATH = $PICO_SDK_PATH"

# ============================================================
# 2. Preparazione cartella build/
# ============================================================
echo "[2/3] Creazione cartella build/"
rm -rf build
mkdir build
cd build

# ============================================================
# 3. CMake + Compilazione
# ============================================================
echo "[3/3] Configurazione e compilazione..."
cmake .. -DPICO_BOARD=pico_w
make -j$(nproc)

echo "=============================================================="
echo " ✔ Compilazione completata!"
echo " ✔ Firmware: build/src/PICO_FREERTOS.uf2"
echo "=============================================================="

