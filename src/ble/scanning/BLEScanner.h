#pragma once

#include <Arduino.h>
#include <BLEDevice.h>

class BLEScanner : BLEAdvertisedDeviceCallbacks {
public:
  // Creates a new instance of `BLEScanner`.
  BLEScanner();

  // Initializes the `BLEScanner`.
  void begin();

  // Starts BLE searching.
  void startSearching(uint8_t *address);

  // Stops BLE searching.
  void stopSearching();

  // Override `BLEAdvertisedDeviceCallbacks`
  void onResult(BLEAdvertisedDevice advertisedDevice);

private:
  BLEScan *_scan;
  BLEAddress _searchingAddress;
};
