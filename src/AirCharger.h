#pragma once

#include <Arduino.h>

#include "ble/BLEPeripheral.h"

class AirChargerClass {
public:
  // Initializes the `AirCharger` with given device name.
  void begin(String deviceName);
};

extern AirChargerClass AirCharger;
