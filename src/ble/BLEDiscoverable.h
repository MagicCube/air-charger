#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEHIDDevice.h>

class BLEDiscoverable : BLEServerCallbacks {
public:
  // Initializes the `BLEDiscoverable`.
  void begin();

  // Starts BLE advertising.
  void startAdvertising();

  // Stops BLE advertising.
  void stopAdvertising();

  // Implements BLEServerCallbacks
  void onConnect(BLEServer *server, esp_ble_gatts_cb_param_t *param);

  // Implements BLEServerCallbacks
  void onDisconnect(BLEServer *server);

private:
  BLEServer *_server;
  BLEHIDDevice *_hid;
  void _setAccessPermission(BLECharacteristic *characteristic);
  void _setAccessPermission(BLEService *service, uint16_t uuid);
};
