#pragma once

#include <Arduino.h>
#include <BLEDevice.h>

#include "../ble_address_t.h"

class BLEScanner : BLEAdvertisedDeviceCallbacks {
public:
  // Creates a new instance of `BLEScanner`.
  BLEScanner();

  // Initializes the `BLEScanner`.
  void begin();

  // Search for device with specific address.
  BLEAdvertisedDevice *search(ble_address_t address);

  // Starts BLE scanning.
  void startScanning();

  // Stops BLE scanning.
  void stopScanning();

  // Continue to search.
  BLEAdvertisedDevice *continueSearching();

  // Implements `BLEAdvertisedDeviceCallbacks`
  void onResult(BLEAdvertisedDevice advertisedDevice);

private:
  BLEAddress _searchingAddress;
  BLEAdvertisedDevice *_foundDevice;
};
