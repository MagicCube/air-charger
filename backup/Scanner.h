#pragma once

#include <Arduino.h>
#include <BLEDevice.h>

class Scanner : BLEAdvertisedDeviceCallbacks {
public:
  BLEAdvertisedDevice *foundDevice = nullptr;

  void start();
  void touch(BLEAdvertisedDevice *device);

  void onResult(BLEAdvertisedDevice advertisedDevice);
};
