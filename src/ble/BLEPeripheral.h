#pragma once

#include <Arduino.h>

#include "conf.h"

#ifdef BLE_ENABLED
#include <BLEDevice.h>
#include "./connecting/BLERemoteDevice.h"
#include "./paring/BLEParingServer.h"
#include "./scanning/BLEScanner.h"
#endif

#include "ble_address_t.h"

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
  void begin(String deviceName);

  BLEPeripheralState state();
  BLERemoteDevice *getRemoteDevice();

  void startParingMode();
  void startScanningMode(ble_address_t addressLookingFor);
  void connect(ble_address_t addressToBeConnected);

private:
  String _deviceName;
  BLEPeripheralState _state = BLEPeripheralState::INITIALIZING;
  #ifdef BLE_ENABLED
  BLEParingServer *_paringServer = nullptr;
  BLEScanner *_scanner = nullptr;
  BLERemoteDevice *_remoteDevice = nullptr;
  #endif
};

extern BLEPeripheralClass BLEPeripheral;
