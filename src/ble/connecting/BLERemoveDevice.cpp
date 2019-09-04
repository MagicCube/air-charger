#include "BLERemoteDevice.h"

#include "../../utils/format.h"
#include "log.h"

static BLERemoteDevice *__instance;
static void __batteryLevelNotifyCallback(BLERemoteCharacteristic *remoteChar, uint8_t *pData,
                                         size_t length, bool isNotify);

BLERemoteDevice::BLERemoteDevice() {
  __instance = this;
}

void BLERemoteDevice::begin() {
  LOG_I("Initializing BLE remote device...");
  _client = BLEDevice::createClient();
  _client->setClientCallbacks(this);
}

void BLERemoteDevice::setCallbacks(BLERemoteDeviceCallbacks *callbacks) {
  _callbacks = callbacks;
}

uint8_t BLERemoteDevice::batteryLevel() {
  return _batteryLevel;
}

void BLERemoteDevice::batteryLevel(uint8_t batteryLevel) {
  if (_batteryLevel != batteryLevel) {
    _batteryLevel = batteryLevel;
    if (_callbacks) {
      _callbacks->onBatteryLevelChanged();
    }
    LOG_D("Battery level is now %d.", _batteryLevel);
  }
}

void BLERemoteDevice::connect(ble_address_t address) {
  _batteryLevel = 0;
  LOG_I("Connecting to remote device [%s]...", formatBLEAddress(address).c_str());
  _client->connect(BLEAddress(address));

  LOG_D("Getting battery service...");
  auto batteryService = _client->getService(BATTERY_SERVICE_UUID);
  if (batteryService != nullptr) {
    LOG_D("Getting battery level characteristic...");
    auto batteryLevelChar = batteryService->getCharacteristic(BATTERY_LEVEL_CHAR_UUID);
    if (batteryLevelChar != nullptr) {
      LOG_D("Readding battery level...");
      batteryLevel(batteryLevelChar->readUInt8());
    }
    if (batteryLevelChar->canNotify()) {
      LOG_D("Subscribing battery level characteristic...");
      batteryLevelChar->registerForNotify(__batteryLevelNotifyCallback);
    }
  }

  LOG_D("Getting time service...");
  auto timeService = _client->getService(TIME_SERVICE_UUID);
  if (timeService != nullptr) {
    LOG_D("Getting time level characteristic...");
    auto currentTimeChar = timeService->getCharacteristic(CURRENT_TIME_CHAR_UUID);
    if (currentTimeChar != nullptr) {
      LOG_D("Reading current time...");
      auto data = currentTimeChar->readValue();
      uint16_t year = data[0] | (data[1] << 8);
      uint8_t month = data[2] - 1;
      uint8_t day = data[3];
      uint8_t hour = data[4];
      uint8_t min = data[5];
      uint8_t sec = data[6];
      if (_callbacks) {
        _callbacks->onTime(DateTime(year, month, day, hour, min, sec));
      }
    }
  }
}

void BLERemoteDevice::onConnect(BLEClient *client) {
  LOG_I("Remote device is now <CONNECTED>.");
  if (_callbacks) {
    _callbacks->onConnect();
  }
}

void BLERemoteDevice::onDisconnect(BLEClient *client) {
  LOG_I("Remote device is now <DISCONNECTED>.");
  if (_callbacks) {
    _callbacks->onDisconnect();
  }
}

static void __batteryLevelNotifyCallback(BLERemoteCharacteristic *remoteChar, uint8_t *data,
                                         size_t length, bool isNotify) {
  if (isNotify && length == 1) {
    LOG_D("Battery level changing notification received.");
    __instance->batteryLevel(data[0]);
  }
}
