#!/bin/bash
set -e

echo "=== Raspberry Pi Pico W FreeRTOS – Setup Semplice e Stabile ==="

echo "[1/6] Creazione cartella lib/"
mkdir -p lib

echo "[2/6] Download Raspberry Pi Pico SDK..."
if [ ! -d "lib/pico-sdk" ]; then
    git clone https://github.com/raspberrypi/pico-sdk lib/pico-sdk
fi

echo "[*] Inizializzo submodules del Pico SDK..."
cd lib/pico-sdk
git submodule update --init --recursive
cd ../..

echo "[3/6] Download FreeRTOS Kernel..."
if [ ! -d "lib/FreeRTOS-Kernel" ]; then
    git clone https://github.com/FreeRTOS/FreeRTOS-Kernel lib/FreeRTOS-Kernel
fi

