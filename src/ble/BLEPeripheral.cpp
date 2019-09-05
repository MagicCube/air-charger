#include "BLEPeripheral.h"

#include "../utils/format.h"
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

BLEPeripheralState BLEPeripheralClass::state() {
  return _state;
}

void BLEPeripheralClass::state(BLEPeripheralState newState) {
  if (_state != newState) {
    _state = newState;
    if (_callbacks) {
      _callbacks->onBLEStateChanged();
    }
  }
}

BLERemoteDevice *BLEPeripheralClass::remoteDevice() {
  return _remoteDevice;
}

void BLEPeripheralClass::setCallbacks(BLEPeripheralCallbacks *callbacks) {
  _callbacks = callbacks;
}

void BLEPeripheralClass::startPairingMode() {
  LOG_I("Starting in <PAIRING> mode...");
  state(BLEPeripheralState::PAIRING);
#ifdef BLE_ENABLED
  if (_pairingServer == nullptr) {
    _pairingServer = new BLEPairingServer();
    _pairingServer->setCallbacks(this);
  }
  _pairingServer->begin(_deviceName);
#endif
}

void BLEPeripheralClass::startScanningMode(ble_address_t addressSearchingFor) {
  LOG_I("Starting in <SCANNING> mode...");
  LOG_I("Searching for device [%s]...", formatBLEAddress(addressSearchingFor).c_str());
  state(BLEPeripheralState::SCANNING);
#ifdef BLE_ENABLED
  if (_scanner == nullptr) {
    _scanner = new BLEScanner();
    _scanner->begin();
  }
  _scanner->search(addressSearchingFor);
#endif
}

void BLEPeripheralClass::continueSearching() {
  auto foundDevice = _scanner->continueSearching();
  if (foundDevice != nullptr) {
    LOG_I("<<< YES, WE FOUND IT >>>");
    state(BLEPeripheralState::REMOTE_DEVICE_READY_TO_CONNECT);
  }
}

void BLEPeripheralClass::connectRemoteDevice(ble_address_t address) {
  LOG_I("Try to connect to [%s]...", formatBLEAddress(address).c_str());
  state(BLEPeripheralState::REMOTE_DEVICE_CONNECTING);
#ifdef BLE_ENABLED
  if (_remoteDevice == nullptr) {
    _remoteDevice = new BLERemoteDevice();
    _remoteDevice->setCallbacks(this);
    _remoteDevice->begin();
  }
  _remoteDevice->connect(address);
#endif
}

void BLEPeripheralClass::onPaired() {
  state(BLEPeripheralState::PAIRED);
}

void BLEPeripheralClass::onConnect() {
  state(BLEPeripheralState::REMOTE_DEVICE_CONNECTED);
  if (_callbacks) {
    _callbacks->onRemoteDeviceConnect();
  }
}

void BLEPeripheralClass::onDisconnect() {
  state(BLEPeripheralState::REMOTE_DEVICE_DISCONNECTED);
  if (_callbacks) {
    _callbacks->onRemoteDeviceDisconnect();
  }
}

void BLEPeripheralClass::onBatteryLevelChanged() {
  if (_callbacks) {
    _callbacks->onRemoteDeviceBatteryLevelChanged();
  }
}

void BLEPeripheralClass::onTime(DateTime time) {
  if (_callbacks) {
    _callbacks->onRemoteDeviceTime(time);
  }
}

BLEPeripheralClass BLEPeripheral;
