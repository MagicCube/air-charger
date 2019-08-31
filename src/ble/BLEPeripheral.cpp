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
}

void BLEPeripheralClass::startParingMode() {
  if (_paringServer == nullptr) {
    _paringServer = new BLEParingServer();
  }
  _paringServer->begin(_deviceName);
}

BLEPeripheralClass BLEPeripheral;
