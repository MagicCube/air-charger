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
  IDLE,
  PARING,
  SCANNING,
  READY_TO_CONNECT,
  CONNECTING,
  CONNECTED,
  DISCONNECTED
};

class BLEPeripheralClass {
public:
  BLEPeripheralState state();

  void begin(String deviceName);
  void startParingMode();
  void startScanningMode(ble_address_t addressLookingFor);
  void connect(ble_address_t addressToBeConnected);

private:
  String _deviceName;
  BLEPeripheralState _state = BLEPeripheralState::INITIALIZING;
  #ifdef BLE_ENABLED
  BLEParingServer *_paringServer = nullptr;
  BLEScanner *_scanner = nullptr;
  #endif
};

extern BLEPeripheralClass BLEPeripheral;
