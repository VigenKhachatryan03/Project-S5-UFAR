# Environmental Monitoring System (ESP8266 + DHT22 + SDS011)

## Project Overview
This project develops a low-cost, IoT-based environmental monitoring system using **ESP8266EX** microcontroller, **DHT22** (temperature and humidity sensor), and **SDS011** (PM2.5/PM10 sensor). Data is sent to a **ThingsBoard** platform in real-time, with **OTA firmware updates**.

## Features
- Real-time monitoring of **temperature**, **humidity**, **PM2.5**, and **PM10**.
- **OTA firmware updates** via GitHub repository.
- **Wi-Fi connectivity** with auto-reconnect.
- **MQTT communication** with ThingsBoard cloud platform.
- Modular firmware design for maintainability.

## Hardware Required
- **ESP8266EX** microcontroller
- **DHT22** temperature & humidity sensor
- **SDS011** Nova PM2.5/PM10 sensor
- **5V DC Brushless Cooling Fan** (optional for airflow)
- **Breadboard** and **USB-UART interface**

## Setup Instructions
1. Clone or download the repository:
   ```bash
   git clone https://github.com/your-username/environmental-monitoring.git
