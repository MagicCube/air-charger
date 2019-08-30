#include "BLEPeripheral.h"

#include "log.h"

void BLEPeripheralClass::begin(String deviceName) {
  LOG_I("Initializing BLE Device [%s]...", deviceName.c_str());
  #ifdef BLE_ENABLED
  _discoverable.begin(deviceName);
  #endif
}

BLEPeripheralClass BLEPeripheral;
