#include "BLEPeripheral.h"

#include "log.h"
#include "../utils/format.h"

BLEPeripheralState BLEPeripheralClass::state() {
  return _state;
}

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

void BLEPeripheralClass::startScanningMode(ble_address_t addressSearchingFor) {
  LOG_I("Starting in <SCANNING> mode...");
  LOG_I("Searching for device [%s]...", formatBLEAddress(addressSearchingFor).c_str());
  _state = BLEPeripheralState::SCANNING;
  if (_scanner == nullptr) {
    _scanner = new BLEScanner();
  }
  _scanner->begin();
  auto foundDevice = _scanner->search(addressSearchingFor);
  if (foundDevice) {
    LOG_I("<<< YES, WE FOUND IT >>>");
    _state = BLEPeripheralState::READY_TO_CONNECT;
  } else {
    _state = BLEPeripheralState::DISCONNECTED;
  }
}

void BLEPeripheralClass::connect(ble_address_t address) {
  LOG_I("Connecting to %s...", formatBLEAddress(address).c_str());
  _state = BLEPeripheralState::CONNECTING;
  auto client = BLEDevice::createClient();
  client->connect(address);
  auto batteryService = client->getService("180f");
  if (batteryService != nullptr) {
    auto characteristic = batteryService->getCharacteristic("2a19");
    if (characteristic != nullptr) {
      LOG_I("Battery level = %d", characteristic->readUInt8());
    }
  }
}

BLEPeripheralClass BLEPeripheral;
