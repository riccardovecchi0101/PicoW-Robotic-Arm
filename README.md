# Pico W Robotic Arm 🤖

A 3D-printed robotic arm controlled by a Raspberry Pi Pico W and FreeRTOS, designed to detect and handle objects moving on a conveyor belt.

## Overview

This project implements a robotic arm controlled by a **Raspberry Pi Pico W** running **FreeRTOS**.

The robotic system combines an **IR sensor**, **servo motors**, a **stepper motor** and a conveyor belt to detect and handle objects.

The mechanical structure of the robotic arm was assembled using **3D-printed components**, while the embedded software coordinates the sensors, motors and robotic movements.

The project focuses on the integration of **real-time embedded programming, motor control, sensor processing and robotics**.

## System Architecture

```text
                         Raspberry Pi Pico W
                                  │
                              FreeRTOS
                                  │
                ┌─────────────────┼─────────────────┐
                │                 │                 │
                ▼                 ▼                 ▼
           IR Sensor        Stepper Motor       Servo Motors
                │                 │                 │
                │                 ▼                 ▼
                │          Conveyor Belt       Robotic Arm
                │
                └──────── Object Detection
```

## Hardware

* Raspberry Pi Pico W
* Servo motors
* Stepper motor
* IR sensor
* Conveyor belt
* 3D-printed robotic arm components
* Stepper motor driver

## Software

* C / C++
* FreeRTOS
* Raspberry Pi Pico SDK
* CMake

## Features

* Real-time task management using FreeRTOS
* IR-based object detection
* Conveyor belt control
* Stepper motor control
* Servo motor control
* Coordinated robotic arm movement
* Raspberry Pi Pico W embedded control
* 3D-printed mechanical components
* Integration of sensors and actuators

## How It Works

Objects are transported along the conveyor belt using a stepper motor.

An **IR sensor positioned above the conveyor belt** detects when an object reaches the designated detection area.

The Raspberry Pi Pico W processes the sensor input and coordinates the robotic system.

The stepper motor controls the conveyor belt, while the servo motors control the robotic arm.

FreeRTOS is used to manage the different activities of the embedded system and coordinate the execution of the various tasks.

## FreeRTOS

The application uses **FreeRTOS** to organize the embedded software into independent real-time tasks.

This allows sensor monitoring, motor control and robotic operations to be handled concurrently while maintaining predictable task execution.

## Hardware Assembly

The robotic arm was physically assembled using **3D-printed components** and integrated with the Raspberry Pi Pico W, motors, sensors and conveyor belt.

## Project Structure

```text
PicoW-Robotic-Arm/
│
├── lib/
│   ├── pico-sdk/
│   └── FreeRTOS-Kernel/
│
├── src/
│   ├── ...
│   └── CMakeLists.txt
│
├── CMakeLists.txt
├── install.sh
├── compile.sh
└── README.md
```

## Build & Installation

Clone the repository:

```bash
git clone https://github.com/riccardovecchi0101/PicoW-Robotic-Arm.git
cd PicoW-Robotic-Arm
```

Install the required dependencies:

```bash
./install.sh
```

Build the project:

```bash
./compile.sh
```

The generated `.uf2` firmware can then be flashed to the Raspberry Pi Pico W.

## Flashing

1. Hold the **BOOTSEL** button while connecting the Raspberry Pi Pico W via USB.
2. The board will appear as the `RPI-RP2` drive.
3. Copy the generated `.uf2` file to the board.
4. The Pico W will reboot and execute the embedded application.

## Credits & Acknowledgements

The project initially used the lightweight FreeRTOS environment provided by:

**Racka98 — PicoW-FreeRTOS-Template**
https://github.com/racka98/PicoW-FreeRTOS-Template

The original template provided the initial project structure and FreeRTOS/Pico W development environment.

The repository was subsequently adapted and extended for the robotic arm project, including the embedded application, sensor integration, motor control, conveyor control and robotic system logic.

## Authors

**Riccardo Vecchi**, **Giuseppe Bellissimo, **Andrea Zappacosta**

GitHub: https://github.com/riccardovecchi0101
