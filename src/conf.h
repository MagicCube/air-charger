#pragma once

// Discoverable Bluetooth device name.
#define DEVICE_NAME "Henry's AirCharger"

// Comment the next line to disable all Bluetooth related features.
// This is very handy when you only want to debug OLED or other
// non-BLE features.
#define BLE_ENABLED

// Comment the next line to disable debug mode.
#define DEBUG

// Comment the next line to disable drawing construction line.
// #define DRAW_CONSTRUCTION_LINE TFT_RED

#define FPS 30

#define UPDATE_INTERVAL (1000 / FPS)

#define NSTARS 32
