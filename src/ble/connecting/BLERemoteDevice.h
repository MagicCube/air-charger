#pragma once

#include <Arduino.h>

#include <BLEDevice.h>

#include "../ble_address_t.h"

#define BATTERY_SERVICE_UUID "180f"
#define BATTERY_LEVEL_CHAR_UUID "2a19"

class BLERemoteDevice : BLEClientCallbacks {
public:
  void begin();

  uint8_t batteryLevel();

  void connect(ble_address_t address);

  void onConnect(BLEClient *client);
  void onDisconnect(BLEClient *client);

private:
  BLEClient *_client;
};
