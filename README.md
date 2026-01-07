# json-meter-serialization
Embedded C library for JSON serialization of smart meter data
# JSON Serialization Library for Embedded Firmware

## Project Overview

This project implements a small, embedded‑friendly **JSON serialization library in C**. It converts structured meter data into a fixed JSON format, simulating part of a smart‑meter / IoT gateway data pipeline. The focus is on **clean code, memory safety, and embedded suitability**.

---

## Platform & Programming Language

* **Language:** C
* **Platform:** Platform‑independent (can run on PC, STM32, ESP32, Arduino)

**Justification:** C is widely used in embedded systems, provides low‑level memory control, and works without external libraries or dynamic memory allocation.

---

## Build and Run Instructions

From the project root directory:

```
gcc examples/main.c src/json_serializer.c -Iinclude -o json_demo
```

Run:

```
./json_demo
```

---

## Public API

```c
typedef struct {
    int meter_id;
    float voltage;
    float current;
    float energy;
} MeterData;
```

```c
int serialize_meter_data(const MeterData *data, char *buffer, int buffer_size);
```

The function serializes meter data into a JSON string stored in a user‑provided buffer.

---

## Example JSON Output

```json
{
  "meter_id": 101,
  "voltage": 230.50,
  "current": 5.20,
  "energy": 12.75
}
```

---

## Design Decisions

* No dynamic memory allocation
* Fixed JSON format
* Safe string handling using `snprintf()`
* Minimal and readable code structure

---

## Possible Extensions

* Support for multiple meters
* Communication over UART/MQTT
* Porting to STM32 HAL / ESP‑IDF
* JSON parsing support

---

**Author:** 3rd Year ENTC Student
