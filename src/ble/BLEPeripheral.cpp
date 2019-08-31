#include "BLEPeripheral.h"

#include "log.h"
#include "../utils/format.h"
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

BLEPeripheralState BLEPeripheralClass::state() {
  return _state;
}

BLERemoteDevice *BLEPeripheralClass::getRemoteDevice() {
  return _remoteDevice;
}

void BLEPeripheralClass::startParingMode() {
  LOG_I("Starting in <PARING> mode...");
  _state = BLEPeripheralState::PARING;
  #ifdef BLE_ENABLED
  if (_paringServer == nullptr) {
    _paringServer = new BLEParingServer();
  }
  _paringServer->begin(_deviceName);
  #endif
}

void BLEPeripheralClass::startScanningMode(ble_address_t addressSearchingFor) {
  LOG_I("Starting in <SCANNING> mode...");
  LOG_I("Searching for device [%s]...", formatBLEAddress(addressSearchingFor).c_str());
  _state = BLEPeripheralState::SCANNING;
  #ifdef BLE_ENABLED
  if (_scanner == nullptr) {
    _scanner = new BLEScanner();
    _scanner->begin();
  }
  auto foundDevice = _scanner->search(addressSearchingFor);
  if (foundDevice) {
    LOG_I("<<< YES, WE FOUND IT >>>");
    _state = BLEPeripheralState::READY_TO_CONNECT;
  } else {
    _state = BLEPeripheralState::DISCONNECTED;
  }
  #endif
}

void BLEPeripheralClass::connect(ble_address_t address) {
  LOG_I("Try to connect to [%s]...", formatBLEAddress(address).c_str());
  _state = BLEPeripheralState::CONNECTING;
  #ifdef BLE_ENABLED
  if (_remoteDevice == nullptr) {
    _remoteDevice = new BLERemoteDevice();
    _remoteDevice->begin();
  }
  _remoteDevice->connect(address);
  #endif
}

BLEPeripheralClass BLEPeripheral;
