#pragma once

#include <Arduino.h>

#include "conf.h"

#ifdef BLE_ENABLED
#include <BLEDevice.h>
#include "./connecting/BLERemoteDevice.h"
#include "./paring/BLEParingServer.h"
#include "./scanning/BLEScanner.h"
#endif

#include "../timing/DateTime.h"
#include "ble_address_t.h"

enum class BLEPeripheralState {
  INITIALIZING,
  IDLE,
  PARING,
  SCANNING,
  REMOTE_DEVICE_READY_TO_CONNECT,
  REMOTE_DEVICE_CONNECTING,
  REMOTE_DEVICE_CONNECTED,
  REMOTE_DEVICE_DISCONNECTED
};

class BLEPeripheralCallbacks {
public:
  virtual void onStateChanged() = 0;
  virtual void onRemoteDeviceConnect() = 0;
  virtual void onRemoteDeviceDisconnect() = 0;
  virtual void onRemoteDeviceTime(DateTime time) = 0;
  virtual void onRemoteDeviceBatteryLevelChanged() = 0;
};

class BLEPeripheralClass : BLERemoteDeviceCallbacks {
public:
  void begin(String deviceName);

  BLEPeripheralState state();
  void setState(BLEPeripheralState newState);
  BLERemoteDevice *getRemoteDevice();
  void setCallbacks(BLEPeripheralCallbacks *callbacks);

  void startParingMode();
  void startScanningMode(ble_address_t addressLookingFor);
  void connectRemoteDevice(ble_address_t remoteAddress);
  void continueSearching();

  // Implements `BLERemoteDeviceCallbacks`.
  void onConnect();
  void onDisconnect();
  void onBatteryLevelChanged();
  void onTime(DateTime time);

private:
  String _deviceName;
  BLEPeripheralState _state = BLEPeripheralState::INITIALIZING;
  BLEPeripheralCallbacks *_callbacks;

  #ifdef BLE_ENABLED
  BLEParingServer *_paringServer = nullptr;
  BLEScanner *_scanner = nullptr;
  BLERemoteDevice *_remoteDevice = nullptr;
  #endif
};

extern BLEPeripheralClass BLEPeripheral;
