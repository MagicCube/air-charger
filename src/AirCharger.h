#pragma once

#include <Arduino.h>

#include <TFT_eSPI.h>

#include "settings/Settings.h"
#include "ble/BLEPeripheral.h"
#include "timing/DateTime.h"
#include "displaying/Screen.h"
#include "charging/Charger.h"

class AirChargerClass : BLEPeripheralCallbacks {
public:
  // Initializes the `AirCharger` with given device name.
  void begin(String deviceName);

  // Event loop.
  uint16_t update();

  // Implements `BLEPeripheralCallbacks`.
  void onStateChanged();
  void onRemoteDeviceConnect();
  void onRemoteDeviceDisconnect();
  void onRemoteDeviceBatteryLevelChanged();
  void onRemoteDeviceTime(DateTime time);

private:
  unsigned long _lastUpdate = 0;
  void _checkConnection();
};

extern AirChargerClass AirCharger;
