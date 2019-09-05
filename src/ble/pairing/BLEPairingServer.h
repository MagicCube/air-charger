#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEHIDDevice.h>

class BLEPairingCallbacks {
public:
  virtual void onPaired() = 0;
};

class BLEPairingServer : BLEServerCallbacks {
public:
  // Initializes the `BLEPairingServer`.
  void begin(String deviceName);

  void setCallbacks(BLEPairingCallbacks *callbacks);

  // Starts BLE advertising.
  void startAdvertising();

  // Stops BLE advertising.
  void stopAdvertising();

  // Implements BLEServerCallbacks.
  void onConnect(BLEServer *server, esp_ble_gatts_cb_param_t *param);
  void onDisconnect(BLEServer *server);

private:
  String _deviceName;
  BLEServer *_server;
  BLEHIDDevice *_hid;
  BLEPairingCallbacks *_callbacks = nullptr;

  void _setAccessPermission(BLECharacteristic *characteristic);
  void _setAccessPermission(BLEService *service, uint16_t uuid);
};
