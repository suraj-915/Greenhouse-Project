# 🌿 Automated Greenhouse Project

An Arduino-powered environmental monitoring and irrigation system. This project tracks soil moisture, ambient temperature, and humidity, displaying real-time data on an I2C LCD and automating a relay-controlled water pump.

## 🚀 Key Features
* **Real-time LCD Dashboard:** Displays Moisture (%), Temperature (°C), and Humidity (%) simultaneously on a 16x2 I2C display.
* **Automated Irrigation Logic:** Automatically toggles a relay based on soil moisture thresholds.
* **Dynamic Sensor Timing:** Uses the `DHT_Unified` library to calculate the optimal delay between sensor readings.
* **Precision Monitoring:** Converts raw analog signals into a user-friendly "Wetness" percentage.

## 🛠️ Hardware Requirements
* **Microcontroller:** Arduino Uno R3
* **Soil Moisture Sensor**
* **Climate Sensor:** DHT11
* **Display:** 16x2 LCD with I2C Backpack
* **Actuator:** 5V Relay Module (for water pump)

## 📊 Logic & Calibration
The system calculates soil "Wetness" using the formula:
$$Wetness = \frac{1023 - SensorData}{1023} \times 100$$

* **Dry Soil (> 650 raw):** The relay is set to `LOW`.
* **Wet Soil (< 650 raw):** The relay is set to `HIGH`.

## 💾 Installation
### Library Dependencies:
* `LiquidCrystal I2C`
* `DHT sensor library` (Adafruit)
* `Adafruit Unified Sensor`
