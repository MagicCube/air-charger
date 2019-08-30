#pragma once

#include <Arduino.h>

#include "conf.h"

#ifdef BLE_ENABLED
#include <BLEDevice.h>
#include "BLEDiscoverable.h"
#endif

class BLEPeripheralClass {
public:
  // Initializes the `BLEPeripheral`.
  void begin(String deviceName);

private:
  #ifdef BLE_ENABLED
  BLEDiscoverable _discoverable;
  #endif
};

extern BLEPeripheralClass BLEPeripheral;
