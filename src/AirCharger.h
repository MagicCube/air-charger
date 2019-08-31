#pragma once

#include <Arduino.h>

#include "ble/BLEPeripheral.h"

class AirChargerClass {
public:
  // Initializes the `AirCharger` with given device name.
  void begin(String deviceName);

  // Event loop.
  void update();

private:
  bool _isEmpty = false;
};

extern AirChargerClass AirCharger;
