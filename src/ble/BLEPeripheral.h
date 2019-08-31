#pragma once

#include <Arduino.h>

#include "conf.h"

#ifdef BLE_ENABLED
#include <BLEDevice.h>
#include "./paring/BLEParingServer.h"
#include "./scanning/BLEScanner.h"
#endif

enum class BLEPeripheralState {
  INITIALIZING,
  PARING,
  SCANNING,
  CONNECTING,
  CONNECTED
};

class BLEPeripheralClass {
public:
  void begin(String deviceName);
  void startParingMode();
  void startScanningMode(uint8_t *addressLookingFor);

private:
  String _deviceName;
  BLEPeripheralState _state = BLEPeripheralState::INITIALIZING;
  #ifdef BLE_ENABLED
  BLEParingServer *_paringServer = nullptr;
  BLEScanner *_scanner = nullptr;
  #endif
};

extern BLEPeripheralClass BLEPeripheral;
