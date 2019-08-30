#include "BLEPeripheral.h"

#include "log.h"

void BLEPeripheralClass::begin(String deviceName) {
  LOG_I("Initializing BLE Device [%s]...", deviceName.c_str());
  #ifdef BLE_ENABLED
  BLEDevice::init(deviceName.c_str());
  _discoverable.begin();
  _discoverable.startAdvertising();
  #endif
}

BLEPeripheralClass BLEPeripheral;
