#include "BLEScanner.h"

#include "../../utils/format.h"
#include "log.h"

BLEScanner::BLEScanner() : _searchingAddress("00:00:00:00:00:00") {
}

void BLEScanner::begin() {
  LOG_I("Initializing BLE scanner...");
}

BLEAdvertisedDevice *BLEScanner::search(ble_address_t address) {
  _searchingAddress = BLEAddress(address);
  startScanning();
  return _foundDevice;
}

void BLEScanner::startScanning() {
  _foundDevice = nullptr;
  auto scan = BLEDevice::getScan();
  scan->setAdvertisedDeviceCallbacks(this, false);
  scan->setInterval(100);
  scan->setWindow(99);
  scan->setActiveScan(true);
  LOG_I("Scanning has been <STARTED>.");
  scan->start(3, false);
  if (_foundDevice) {
    LOG_D(">>> I'M FEELING GOOD <<< Found device in less than 3 seconds");
  }
}

BLEAdvertisedDevice *BLEScanner::continueSearching() {
  auto scan = BLEDevice::getScan();
  scan->start(1, true);
  return _foundDevice;
}

void BLEScanner::stopScanning() {
  BLEDevice::getScan()->stop();
  LOG_I("Scanning has been <STOPPED>.");
}

void BLEScanner::onResult(BLEAdvertisedDevice device) {
  // LOG_D("BLE Advertised Device found: %s, RSSI = %d", device.getAddress().toString().c_str(),
  //       device.getRSSI());
  if (device.getAddress().equals(_searchingAddress)) {
    stopScanning();
    _foundDevice = &device;
  }
}
