# Raspberry Pi Pico W FreeRTOS – Ready-to-Use Template

This repository provides a **fully self-contained environment** for developing FreeRTOS-based applications on the **Raspberry Pi Pico W**.  
Everything you need — the Pico SDK, the FreeRTOS Kernel, and the CMake configuration — is already included and ready to build out of the box.

---

## 🧩 Features
- ✅ **Fully portable** — no dependencies or setup required  
- 🧠 **FreeRTOS Kernel** and **Pico SDK** already included in the `lib/` folder  
- ⚙️ Preconfigured **CMake toolchain** (no need for environment variables)  
- 🚀 Works immediately with Raspberry Pi Pico W  
- 💡 Includes a minimal working example (`try.c`) that blinks the onboard LED  

---

## 📁 Project Structure

```
PicoW-Robotic-Arm/
│
├── lib/
│   ├── FreeRTOS-Kernel/       → FreeRTOS source and portable files
│   └── pico-sdk/              → Official Raspberry Pi Pico SDK
│
├── src/
│   ├── try.c                  → Example FreeRTOS application (LED blink)
│   └── CMakeLists.txt         → Source configuration
│
├── CMakeLists.txt             → Root project file
├── .gitignore                 → Git configuration
└── README.md                  → Project documentation
```

> ⚙️ **Note:**  
> The `lib/` directory **already contains**:
> - `lib/pico-sdk` → the official Raspberry Pi Pico SDK  
> - `lib/FreeRTOS-Kernel` → the FreeRTOS kernel source  
>
> This makes the repository **fully portable**. You can clone and build immediately, even offline.

---

## 🚀 Getting Started

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/riccardovecchi0101/PicoW-Robotic-Arm.git
cd PicoW-Robotic-Arm
```

No extra setup required — the SDK and FreeRTOS are already included.

---

### 2️⃣ Build the Project
```bash
mkdir build
cd build
cmake .. -DPICO_BOARD=pico_w
make
```

After a successful compilation, a `.uf2` firmware file named:

```
build/src/PICO_FREERTOS.uf2
```

will be generated.

---

### 3️⃣ Flash to Pico W
1. Hold down the **BOOTSEL** button while connecting the Pico W to your computer via USB.  
2. A new storage drive (`RPI-RP2`) will appear.  
3. Drag and drop the generated UF2 file:
   ```
   build/src/PICO_FREERTOS.uf2
   ```
4. The board will reboot automatically and start running your FreeRTOS program.

If everything works correctly, the onboard LED will blink — confirming that your setup is functional.

---

## 🧠 Customization
- Modify or replace `src/try.c` to create your own application.  
- Update the `add_executable()` section in `src/CMakeLists.txt` if you change filenames.  
- Re-run `cmake .. && make` to rebuild.  

---

## 🧾 Credits & Inspiration
This repository is based on and inspired by  
👉 [racka98/PicoW-FreeRTOS-Template](https://github.com/racka98/PicoW-FreeRTOS-Template),  
but it has been reworked to be **completely self-contained**, requiring **no submodules, no SDK downloads, and no external setup**.

---

## ⚙️ Troubleshooting

### 🧩 Common Issues
- **CMake cannot find SDK or FreeRTOS:**  
  Ensure that both folders exist inside `lib/`:
  ```
  lib/pico-sdk/
  lib/FreeRTOS-Kernel/
  ```
  They are included by default — if missing, reclone the repository.

- **No LED blinking:**  
  Check that the correct `.uf2` file was flashed and that your board is a **Raspberry Pi Pico W**.

---

## 🛠️ Updating SDK or FreeRTOS (optional)

If you ever want to update the included libraries:

### 🔹 Update Pico SDK
```bash
cd lib/pico-sdk
git pull origin master
```

### 🔹 Update FreeRTOS Kernel
```bash
cd lib/FreeRTOS-Kernel
git pull origin main
```

> ⚠️ Always verify that your `CMakeLists.txt` and include paths remain valid after updates,  
> since newer SDK or FreeRTOS versions may introduce structural changes.

---

### 🧰 Outputs
After a successful build, you’ll find your firmware here:
```
build/src/PICO_FREERTOS.uf2
```

---


