#include "BLEScanner.h"

#include "../../utils/format.h"
#include "log.h"

BLEScanner::BLEScanner() : _searchingAddress("00:00:00:00:00:00") {
}

void BLEScanner::begin() {
  LOG_I("Initializing BLE scanner...");
  _scan = BLEDevice::getScan();
  _scan->setAdvertisedDeviceCallbacks(this);
}

BLEAdvertisedDevice *BLEScanner::search(ble_address_t address) {
  _foundDevice = nullptr;
  _searchingAddress = BLEAddress(address);
  startScanning();
  return _foundDevice;
}

BLEAdvertisedDevice *BLEScanner::startScanning() {
  _scan->setInterval(1000);
  _scan->setWindow(500);
  _scan->setActiveScan(true);
  LOG_I("Scanning has been <STARTED>.");
  _scan->start(60 * 60 * 24 * 365, true);
  return _foundDevice;
}

void BLEScanner::stopScanning() {
  _scan->stop();
  LOG_I("Scanning has been <STOPPED>.");
}

void BLEScanner::onResult(BLEAdvertisedDevice device) {
  LOG_I("BLE Advertised Device found: %s, RSSI = %d", device.getAddress().toString().c_str(),
        device.getRSSI());
  if (device.getAddress().equals(_searchingAddress)) {
    stopScanning();
    _foundDevice = &device;
  }
}
