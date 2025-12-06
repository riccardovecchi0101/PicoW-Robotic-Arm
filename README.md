# Raspberry Pi Pico W FreeRTOS – Lightweight Template

This repository provides a **clean and lightweight environment** for developing FreeRTOS-based applications on the **Raspberry Pi Pico W**.  
It is designed to be **modular**, letting you decide which SDK and kernel versions to use, while keeping the repository small and easy to maintain.

---

## 🧩 Features
- 🧠 Compatible with **Raspberry Pi Pico SDK** and **FreeRTOS Kernel**
- ⚙️ Preconfigured **CMake toolchain**
- 🚀 Works immediately with Raspberry Pi Pico W
- 💡 Includes a minimal working example (`try.c`) that blinks the onboard LED

---

## 📁 Project Structure
```
PicoW-Robotic-Arm/
│
├── lib/                     → place SDKs here
│   ├── pico-sdk/            → Raspberry Pi Pico SDK (to be downloaded)
│   └── FreeRTOS-Kernel/     → FreeRTOS Kernel (to be downloaded)
│
├── src/
│   ├── try.c                → Example FreeRTOS application
│   └── CMakeLists.txt       → Source configuration
│
├── CMakeLists.txt           → Root project file
└── README.md                → Project documentation
```

> ⚙️ **Note:**  
> The `lib/` directory **must contain** the following two components before building:  
> - `lib/pico-sdk` → [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)  
> - `lib/FreeRTOS-Kernel` → [FreeRTOS Kernel](https://github.com/FreeRTOS/FreeRTOS-Kernel)

---

The easiest and fastest way to prepare the project is to use the included **install.sh** script.

Run:

./install.sh


Compile:

./compile.sh

## 🔌 Flashing to Pico W
1. Hold down the **BOOTSEL** button while connecting the Pico W via USB  
2. A new drive (`RPI-RP2`) will appear  
3. Drag and drop the `.uf2` file:
   ```
   build/src/PICO_FREERTOS.uf2
   ```
4. The board will reboot automatically and start running the example program (LED blink)

---

## 🧠 Customization
- Edit or replace `src/try.c` to create your own FreeRTOS application  
- Update `src/CMakeLists.txt` if you change source file names  
- Re-run `cmake .. && make` to rebuild

---

## 🧾 Credits & Inspiration
Based on and inspired by  
👉 [racka98/PicoW-FreeRTOS-Template](https://github.com/racka98/PicoW-FreeRTOS-Template)  
Adapted to serve as a **lightweight, modular template** for your own FreeRTOS-based Pico W projects.

---

