#include "BLEParingServer.h"

#include "log.h"

#include "../../settings/Settings.h"
#include "../../utils/format.h"

#include "KeyboardReportMap.h"

void BLEParingServer::begin(String deviceName) {
  _deviceName = deviceName;

  LOG_I("Initializing BLE paring server...");
  _server = BLEDevice::createServer();
  _server->setCallbacks(this);

  // HID Decoy
  LOG_D("Initializing HID device...");
  _hid = new BLEHIDDevice(_server);

  // Input / Output
  LOG_D("Initializing HID service...");
  auto _inputCharacteristic = _hid->inputReport(1);
  _setAccessPermission(_inputCharacteristic);
  auto outputCharacteristic = _hid->outputReport(1);
  _setAccessPermission(outputCharacteristic);

  // Disable security.
  LOG_D("Setting HID security...");
  BLESecurity *security = new BLESecurity();
  security->setCapability(ESP_IO_CAP_NONE);

  LOG_D("Setting HID permissions...");
  _setAccessPermission(_hid->deviceInfo(), 0x2a50);
  _hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  _setAccessPermission(_hid->hidService(), 0x2a4a);
  _setAccessPermission(_hid->hidService(), 0x2a4b);
  _setAccessPermission(_hid->hidService(), 0x2a4c);
  _setAccessPermission(_hid->hidService(), 0x2a4e);
  _setAccessPermission(_hid->batteryService(), 0x2a19);

  LOG_D("Setting device country and flags...");
  _hid->hidInfo(0x00, 0x01);

  LOG_D("Setting battery level...");
  _hid->setBatteryLevel(100);

  // Send HID report map.
  LOG_D("Setting HID report map...");
  _hid->reportMap((uint8_t *)KEYBOARD_REPORT_MAP, sizeof(KEYBOARD_REPORT_MAP));

  LOG_D("Starting HID service...");
  // Start HID service.
  _hid->startServices();
  LOG_D("HID service has been <STARTED>.");
  LOG_I("BLE paring server has been <INITIALIZED>.");

  startAdvertising();
}

void BLEParingServer::startAdvertising() {
  LOG_D("Starting BLE advertising...");
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  // Pretend to be an HID keyboard device.
  advertising->setAppearance(GENERIC_HID);
  advertising->addServiceUUID(_hid->hidService()->getUUID());
  // advertising->setScanResponse(true);
  // Functions that help with iOS connections issue
  // advertising->setMinPreferred(0x06);
  // advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  LOG_I("BLE advertising has been <STARTED>.");
  LOG_I("Search [%s] in your Bluetooth device list.", _deviceName.c_str());
  LOG_I("Waiting for paring with new device...");
}

void BLEParingServer::stopAdvertising() {
  LOG_D("Stopping advertising...");
  _server->getAdvertising()->stop();
  LOG_I("BLE advertising has been <STOPPED>.");
}

void BLEParingServer::onConnect(BLEServer *server, esp_ble_gatts_cb_param_t *param) {
  LOG_I("A new client [%s] has been paired.", formatBLEAddress(param->connect.remote_bda).c_str());
  LOG_I("Saving paired client address...");
  AirChargerSettings.setClientAddress((ble_address_t)(param->connect.remote_bda));
  AirChargerSettings.save();
}

void BLEParingServer::onDisconnect(BLEServer *server) {
}


void BLEParingServer::_setAccessPermission(BLECharacteristic *characteristic) {
  characteristic->setAccessPermissions(ESP_GATT_PERM_READ_ENCRYPTED |
                                       ESP_GATT_PERM_WRITE_ENCRYPTED);

  auto desc = characteristic->getDescriptorByUUID(BLEUUID((uint16_t)0x2904));
  if (desc) {
    desc->setAccessPermissions(ESP_GATT_PERM_READ_ENCRYPTED | ESP_GATT_PERM_WRITE_ENCRYPTED);
  }

  desc = characteristic->getDescriptorByUUID(BLEUUID((uint16_t)0x2908));
  if (desc) {
    desc->setAccessPermissions(ESP_GATT_PERM_READ_ENCRYPTED | ESP_GATT_PERM_WRITE_ENCRYPTED);
  }

  desc = characteristic->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  if (desc) {
    desc->setAccessPermissions(ESP_GATT_PERM_READ_ENCRYPTED | ESP_GATT_PERM_WRITE_ENCRYPTED);
  }
}

void BLEParingServer::_setAccessPermission(BLEService *service, uint16_t uuid) {
  _setAccessPermission(service->getCharacteristic(BLEUUID(uuid)));
}
