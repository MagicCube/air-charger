#include "BLEPeripheral.h"

#include "log.h"

void BLEPeripheralClass::begin(String deviceName) {
  _deviceName = deviceName;
  LOG_I("Initializing BLE peripheral [%s]...", deviceName.c_str());
  #ifdef BLE_ENABLED
  LOG_D("Initializing BLE device...");
  BLEDevice::init(deviceName.c_str());
  LOG_D("Setting encryption level...");
  // Add encryption to built-in characteristics and descirptors.
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);
  #endif
  LOG_I("BLE peripheral has been <INITIALIZED>.");
}

void BLEPeripheralClass::startParingMode() {
  LOG_I("Starting in <PARING> mode...");
  _state = BLEPeripheralState::PARING;
  if (_paringServer == nullptr) {
    _paringServer = new BLEParingServer();
  }
  _paringServer->begin(_deviceName);
}

void BLEPeripheralClass::startScanningMode(uint8_t *addressSearchingFor) {
  LOG_I("Starting in <SCANNING> mode...");
  _state = BLEPeripheralState::SCANNING;
  if (_scanner == nullptr) {
    _scanner = new BLEScanner();
  }
  _scanner->begin();
  _scanner->startSearching(addressSearchingFor);
}

BLEPeripheralClass BLEPeripheral;
