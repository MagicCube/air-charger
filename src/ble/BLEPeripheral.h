#pragma once

#include <Arduino.h>

#include "conf.h"

#ifdef BLE_ENABLED
#include <BLEDevice.h>
#include "./paring/BLEParingServer.h"
#endif

class BLEPeripheralClass {
public:
  // Initializes the `BLEPeripheral`.
  void begin(String deviceName);
  void startParingMode();

private:
  String _deviceName;
  #ifdef BLE_ENABLED
  BLEParingServer *_paringServer = nullptr;
  #endif
};

extern BLEPeripheralClass BLEPeripheral;
