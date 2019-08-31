#pragma once

#include <Arduino.h>

#include <TFT_eSPI.h>

#include "timing/DateTime.h"
#include "ble/BLEPeripheral.h"


class AirChargerClass : BLEPeripheralCallbacks {
public:
  // Initializes the `AirCharger` with given device name.
  void begin(String deviceName);

  // Event loop.
  void update();

  void redraw();
  void drawMessage(String message);

  // Implements `BLEPeripheralCallbacks`.
  void onRemoteDeviceConnect();
  void onRemoteDeviceDisconnect();
  void onRemoteDeviceBatteryLevelChanged();
  void onRemoteDeviceTime(DateTime time);

private:
  TFT_eSPI _display;
};

extern AirChargerClass AirCharger;
