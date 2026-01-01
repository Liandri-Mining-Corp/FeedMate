# FeedMate

**FeedMate** is ESP32 firmware for controlling an automatic food dispenser.  
This repository contains Arduino-compatible sketches that enable Wi-Fi control, sensor integration, display support, and actuation of the feeder mechanism.

> **Please note:** This project was created as a **school project** and is **not intended for production or general use**.  
> It was developed in conjunction with a **specific physical construction**.
>
> Feel free to fork the repository and build upon it, adapt it, or use it as inspiration for your own projects. 😄

---

## 🚀 Overview

FeedMate provides core firmware to operate an ESP32-based food dispenser. The ESP32 runs web server functionality and controls the following subsystems:

- Servo motor for dispensing food  
- Ultrasonic sensor to detect whether sufficient food is loaded  
- Moisture and temperature sensing  
- RFID reader support  
- LED status indicators  
- Display interface  
- Timer-based feeding control  

---

## 📁 Repository Contents

| File / Folder | Purpose |
|---------------|---------|
| `FeedMate.ino` | Main application code |
| `WebServer.ino` | Wi-Fi and web server logic |
| `display.ino` | Display handling (screen UI) |
| `feeder_servo.ino` | Servo control for dispenser |
| `led_controller.ino` | LED status controller |
| `moisture_sensor.ino` | Moisture / food level sensing |
| `rfid_reader.ino` | Optional RFID support |
| `service_hatch.ino` | Service hatch control logic |
| `timer.ino` | Time-based feeding routines |
| `ultrasonic_sensor.ino` | Distance / presence sensing |
| `libraries/` | Bundled libraries and support headers |

---

## 🛠 Features

- **Wi-Fi-enabled web server** for real-time status monitoring  
- **Modular codebase** with separate files for different hardware modules  
- **Sensor integration** (ultrasonic, moisture, RFID) for monitoring  
- **Display support** for local status readout  

---

## 🧰 Prerequisites

Before building and uploading, make sure you have:

- **Arduino IDE** installed  
- **ESP32 board support** configured in the Arduino IDE Boards Manager  
- Latest **ESP32 libraries and dependencies**  
- Hardware assembled with the ESP32 connected to:
  - Servo motor  
  - Ultrasonic sensor  
  - Display  
  - Any additional modules being used  

---

## 📲 Installation & Setup

1. Clone this repository:
   ```bash
   git clone https://github.com/Liandri-Mining-Corp/FeedMate.git
2. Open FeedMate.ino in the Arduino IDE.

3. Install the required libraries (ESP32 Wi-Fi, WebServer, Servo, display libraries, etc.).

4. Configure your Wi-Fi credentials in the code.

5. Select your ESP32 board and the correct COM port.

6. Upload the firmware to your ESP32.

(Optional) Power-cycle the board and connect it to the configured Wi-Fi network.
