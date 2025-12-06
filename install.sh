#!/bin/bash

set -e

# ============================
# CONFIG
# ============================

USE_SUBMODULES=true   # metti false per clone normale
SDK_DIR="lib/pico-sdk"
FREERTOS_DIR="lib/FreeRTOS-Kernel"

echo "=== Raspberry Pi Pico W FreeRTOS Template Setup ==="

# ============================
# 1. Creazione cartella lib/
# ============================
echo "[1/5] Creazione cartella lib/"
mkdir -p lib

# ============================
# 2. Download dipendenze
# ============================

if [ "$USE_SUBMODULES" = true ]; then
    echo "[2/5] Inizializzazione submodules..."
    git submodule add https://github.com/raspberrypi/pico-sdk $SDK_DIR || true
    git submodule add https://github.com/FreeRTOS/FreeRTOS-Kernel $FREERTOS_DIR || true
    git submodule update --init --recursive
else
    echo "[2/5] Download manuale repository..."
    
    if [ ! -d "$SDK_DIR" ]; then
        git clone https://github.com/raspberrypi/pico-sdk $SDK_DIR
    fi
    
    if [ ! -d "$FREERTOS_DIR" ]; then
        git clone https://github.com/FreeRTOS/FreeRTOS-Kernel $FREERTOS_DIR
    fi
fi

# ============================
# 3. Preparazione build/
# ============================
echo "[3/5] Creazione cartella build/"
rm -rf build
mkdir build
cd build

# ============================
# 4. Configurazione CMake
# ============================
echo "[4/5] Esecuzione CMake..."
cmake .. -DPICO_BOARD=pico_w

# ============================
# 5. Compilazione
# ============================
echo "[5/5] Compilazione..."
make -j$(nproc)

echo "============================================="
echo "  ✔ Build completata!"
echo "  Firmware generato in: build/src/PICO_FREERTOS.uf2"
echo "============================================="

