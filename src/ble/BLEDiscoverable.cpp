#include "BLEDiscoverable.h"

#include "conf.h"
#include "log.h"

#include "../settings/Settings.h"

#include "KeyboardReportMap.h"

void BLEDiscoverable::begin(String deviceName) {
  LOG_I("Initializing BLE discoverable server...");

  _deviceName = deviceName;
  LOG_D("Initializing BLE device...");
  BLEDevice::init(deviceName.c_str());

  LOG_D("Setting encryption level...");
  // Add encryption to built-in characteristics and descirptors.
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);

  LOG_D("Initializing BLE discoverable server...");
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
  LOG_I("BLE discoverable server has been <INITIALIZED>.");

  startAdvertising();
}

void BLEDiscoverable::startAdvertising() {
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

void BLEDiscoverable::stopAdvertising() {
  LOG_D("Stopping advertising...");
  _server->getAdvertising()->stop();
  LOG_I("BLE advertising has been <STOPPED>.");
}

void BLEDiscoverable::onConnect(BLEServer *server, esp_ble_gatts_cb_param_t *param) {
  BLEAddress clientAddress = BLEAddress(param->connect.remote_bda);
  LOG_I("A new client [%s] has been paired.", clientAddress.toString().c_str());
  LOG_I("Saving paired client address...");
  AirChargerSettings.setClientAddress((uint8_t *)(param->connect.remote_bda));
  AirChargerSettings.save();
}

void BLEDiscoverable::onDisconnect(BLEServer *server) {
}


void BLEDiscoverable::_setAccessPermission(BLECharacteristic *characteristic) {
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

void BLEDiscoverable::_setAccessPermission(BLEService *service, uint16_t uuid) {
  _setAccessPermission(service->getCharacteristic(BLEUUID(uuid)));
}
