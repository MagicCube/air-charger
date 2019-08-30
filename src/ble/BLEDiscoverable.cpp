#include "BLEDiscoverable.h"

#include "conf.h"
#include "log.h"

#include "KeyboardReportMap.h"

void BLEDiscoverable::begin() {
  _server = BLEDevice::createServer();
  _server->setCallbacks(this);

  // HID Decoy
  _hid = new BLEHIDDevice(_server);

  // Input / Output
  auto _inputCharacteristic = _hid->inputReport(1);
  _setAccessPermission(_inputCharacteristic);
  auto outputCharacteristic = _hid->outputReport(1);
  _setAccessPermission(outputCharacteristic);

  // Disable security.
  BLESecurity *security = new BLESecurity();
  security->setCapability(ESP_IO_CAP_NONE);

  // Add encryption to built-in characteristics and descirptors.
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);
  _setAccessPermission(_hid->deviceInfo(), 0x2a50);
  _hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  _setAccessPermission(_hid->hidService(), 0x2a4a);
  _setAccessPermission(_hid->hidService(), 0x2a4b);
  _setAccessPermission(_hid->hidService(), 0x2a4c);
  _setAccessPermission(_hid->hidService(), 0x2a4e);
  _setAccessPermission(_hid->batteryService(), 0x2a19);

  // Set device info.
  _hid->hidInfo(0x00, 0x01);
  _hid->manufacturer(DEVICE_MANUFACTURER);
  _hid->setBatteryLevel(100);

  // Send HID report.
  _hid->reportMap((uint8_t *)KEYBOARD_REPORT_MAP, sizeof(KEYBOARD_REPORT_MAP));

  // Start HID service.
  _hid->startServices();
}

void BLEDiscoverable::startAdvertising() {
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  // Pretend to be an HID keyboard device.
  advertising->setAppearance(GENERIC_HID);
  advertising->addServiceUUID(_hid->hidService()->getUUID());
  advertising->setScanResponse(true);
  // Functions that help with iOS connections issue
  advertising->setMinPreferred(0x06);
  advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  LOG_I("BLE advertising has been <STARTED>.");
  LOG_I("Search [%s] in your Bluetooth device list.", DEVICE_NAME);
}

void BLEDiscoverable::onConnect(BLEServer *server, esp_ble_gatts_cb_param_t *param) {
  BLEAddress clientAddress = BLEAddress(param->connect.remote_bda);
  LOG_I("A new client has been connected [%s].", clientAddress.toString().c_str());
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
