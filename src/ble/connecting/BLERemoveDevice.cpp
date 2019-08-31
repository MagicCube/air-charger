#include "BLERemoteDevice.h"

#include "log.h"
#include "../../utils/format.h"

static uint8_t _batteryLevel;
static void _batteryLevelNotifyCallback(BLERemoteCharacteristic *remoteChar,
                                                        uint8_t *pData, size_t length,
                                                        bool isNotify);

void BLERemoteDevice::begin() {
  LOG_I("Initializing BLE remote device...");
  _client = BLEDevice::createClient();
  _client->setClientCallbacks(this);
}

uint8_t BLERemoteDevice::batteryLevel() {
  return _batteryLevel;
}

void BLERemoteDevice::connect(ble_address_t address) {
  LOG_I("Connecting to remote device [%s]...", formatBLEAddress(address).c_str());
  _client->connect(BLEAddress(address));
  LOG_D("Getting battery service...");
  auto batteryService = _client->getService(BATTERY_SERVICE_UUID);
  if (batteryService != nullptr) {
    LOG_D("Getting battery level characteristic...");
    auto batteryLevelChar = batteryService->getCharacteristic(BATTERY_LEVEL_CHAR_UUID);
    if (batteryLevelChar != nullptr) {
      LOG_D("Readding battery level...");
      _batteryLevel = batteryLevelChar->readUInt8();
      LOG_D("Battery level is now %d.", _batteryLevel);
    }
    if (batteryLevelChar->canNotify()) {
      LOG_D("Subscribing battery level characteristic...");
      batteryLevelChar->registerForNotify(_batteryLevelNotifyCallback);
    }
  }
}

void BLERemoteDevice::onConnect(BLEClient *client) {
  LOG_I("Remote device is now <CONNECTED>.");
}

void BLERemoteDevice::onDisconnect(BLEClient *client) {
  LOG_I("Remote device is now <DISCONNECTED>.");
}

static void _batteryLevelNotifyCallback(
  BLERemoteCharacteristic* remoteChar,
  uint8_t* data,
  size_t length,
  bool isNotify) {
  if (isNotify && length == 1) {
    LOG_D("Battery level changing notification received.");
    LOG_D("Battery level is now %d", data[0]);
    _batteryLevel = data[0];
  }
}
