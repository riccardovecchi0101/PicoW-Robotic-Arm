# Raspberry Pi Pico W FreeRTOS – Ready-to-Use Template

This repository provides a **ready-to-use environment** for developing FreeRTOS-based applications on the **Raspberry Pi Pico W**. Everything is already set up — you just need to clone, build, and flash.

---

## 🧩 Features
- **FreeRTOS Kernel** and **Pico SDK** already included under `lib/`
- Fully configured **CMake toolchain** (no need to set environment variables)
- Works **out of the box** with Raspberry Pi Pico W
- Includes a minimal working example (`try.c`) that blinks the onboard LED

---

## 🚀 Getting Started

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/riccardovecchi0101/PicoW-Robotic-Arm.git
cd PicoW-Robotic-Arm
```

Everything you need (SDK + FreeRTOS) is already inside the `lib/` folder — no need to install or export extra paths.

---

### 2️⃣ Build the Project
```bash
mkdir build
cd build
cmake .. -DPICO_BOARD=pico_w
make
```

The compilation should complete successfully, producing a `.uf2` firmware file named `PICO_FREERTOS.uf2` in `build/src/`.

---

### 3️⃣ Flash to Pico W
1. Hold down the **BOOTSEL** button while connecting the Pico W to your computer via USB.
2. A new storage drive (named `RPI-RP2`) will appear.
3. Drag-and-drop the generated UF2 file:
   ```
   build/src/PICO_FREERTOS.uf2
   ```
4. The board will reboot automatically and start running the program.

The included example (`try.c`) will make the onboard LED blink under FreeRTOS — confirming that your environment works perfectly.

---

## 🧠 Customization
- To build your own application, modify or replace `src/try.c`.
- Update the `add_executable()` section in `src/CMakeLists.txt` if you change filenames.
- Re-run `cmake .. && make` to rebuild.

---

## 🧾 Credits & Inspiration
This repository is based on and inspired by [racka98/PicoW-FreeRTOS-Template](https://github.com/racka98/PicoW-FreeRTOS-Template), with additional configuration to make it **self-contained** and **ready to compile immediately** without external dependencies or environment variables.

---

### 🧰 Outputs
After a successful build, you’ll find your firmware here:
```
build/src/PICO_FREERTOS.uf2
```

---

## ⚙️ Troubleshooting

### 🧩 Common Issues
- **CMake cannot find SDK or FreeRTOS:**  
  Ensure that both are located inside the `lib/` directory (they are included by default in this repository).

- **No LED blinking:**  
  Make sure you flashed the correct `.uf2` file and that your board is a **Raspberry Pi Pico W**.

- **`Permission denied` when flashing:**  
  Ensure your user has write access to the mounted `RPI-RP2` drive or retry as administrator.

---
