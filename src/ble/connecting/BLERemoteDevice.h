#pragma once

#include <Arduino.h>

#include <BLEDevice.h>

#include "../ble_address_t.h"
#include "../../timing/DateTime.h"

#define BATTERY_SERVICE_UUID "180f"
#define BATTERY_LEVEL_CHAR_UUID "2a19"

#define TIME_SERVICE_UUID "1805"
#define CURRENT_TIME_CHAR_UUID "2a2b"

class BLERemoteDeviceCallbacks {
public:
  virtual void onConnect() = 0;
  virtual void onDisconnect() = 0;
  virtual void onBatteryLevelChanged() = 0;
  virtual void onTime(DateTime time) = 0;
};

class BLERemoteDevice : BLEClientCallbacks {
public:
  BLERemoteDevice();
  void begin();

  uint8_t batteryLevel();
  void setBatteryLevel(uint8_t batteryLevel);
  void setCallbacks(BLERemoteDeviceCallbacks *callbacks);

  void connect(ble_address_t address);

  void onConnect(BLEClient *client);
  void onDisconnect(BLEClient *client);

private:
  uint8_t _batteryLevel = 0;
  BLEClient *_client;
  BLERemoteDeviceCallbacks *_callbacks;
};
