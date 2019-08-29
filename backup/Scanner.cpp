#include "Scanner.h"

static BLEAddress DEVICE_ADDRESS("7d:ce:86:7c:e7:d9");
static BLEUUID DEVICE_INFO_SERVICE_UUID("180a");
static BLEUUID MANUFACTURER_NAME_CHARACTERISTIC_UUID("2a29");
static BLEUUID MODEL_NUMBER_CHARACTERISTIC_UUID("2a24");

static BLEUUID BATTERY_SERVICE_UUID("180f");
static BLEUUID BATTERY_LEVEL_CHARACTERISTIC_UUID("2a19");

void Scanner::start() {
  Serial.begin(115200);
  Serial.print("Start scanning...");
  auto bleScan = BLEDevice::getScan();
  bleScan->setAdvertisedDeviceCallbacks(this);
  bleScan->setInterval(1349);
  bleScan->setWindow(449);
  bleScan->setActiveScan(true);
  bleScan->start(5, false);
}

void Scanner::onResult(BLEAdvertisedDevice device) {
  Serial.println("\n**********************************************************************************");
  Serial.print("BLE Device found: ");
  Serial.println(device.toString().c_str());
  Serial.print("RSSI = ");
  Serial.println(device.getRSSI());
  if (device.getAddress().equals(DEVICE_ADDRESS)) {
    foundDevice = new BLEAdvertisedDevice(device);
  }
}

void Scanner::touch(BLEAdvertisedDevice *device) {
  delay(1000);
  Serial.print("Connecting to ");
  Serial.print(device->toString().c_str());
  Serial.println("...");
  auto client = BLEDevice::createClient();
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);
  client->connect(device);
  Serial.println("Connected");
  auto service = client->getService(DEVICE_INFO_SERVICE_UUID);
  if (service != nullptr) {
    auto characteristic = service->getCharacteristic(MANUFACTURER_NAME_CHARACTERISTIC_UUID);
    if (characteristic != nullptr) {
      auto value = characteristic->readValue().c_str();
      Serial.print("Manufacturer Name = ");
      Serial.println(value);
    }
    characteristic = service->getCharacteristic(MODEL_NUMBER_CHARACTERISTIC_UUID);
    if (characteristic != nullptr) {
      auto value = characteristic->readValue().c_str();
      Serial.print("Model Number = ");
      Serial.println(value);
    }
  }
  service = client->getService(BATTERY_SERVICE_UUID);
  if (service != nullptr) {
    auto characteristic = service->getCharacteristic(BATTERY_LEVEL_CHARACTERISTIC_UUID);
    if (characteristic != nullptr) {
      auto value = characteristic->readUInt8();
      Serial.print("Battery Level = ");
      Serial.println(value);
    }
  }
  client->disconnect();
}
