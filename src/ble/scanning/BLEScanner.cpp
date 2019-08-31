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

void BLEScanner::startSearching(uint8_t *address) {
  _searchingAddress = BLEAddress(address);
  LOG_I("Searching for device [%s]...", _searchingAddress.toString().c_str());
  _scan->setInterval(1000);
  _scan->setWindow(500);
  _scan->setActiveScan(true);
  LOG_I("Scanning has been <STARTED>.");
  _scan->start(60 * 60 * 24 * 365, true);
}

void BLEScanner::stopSearching() {
  _searchingAddress = BLEAddress("00:00:00:00:00:00");
  _scan->stop();
  LOG_I("Scanning has been <STOPPED>.");
}

void BLEScanner::onResult(BLEAdvertisedDevice device) {
  LOG_I("BLE Advertised Device found: %s, RSSI = %d", device.getAddress().toString().c_str(),
        device.getRSSI());
  if (device.getAddress().equals(_searchingAddress)) {
    LOG_I("<YES, WE FOUND IT>");
    stopSearching();
  }
}
