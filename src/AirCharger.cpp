#include "AirCharger.h"

void AirChargerClass::begin(String deviceName) {
  BLEPeripheral.begin(deviceName);
}

AirChargerClass AirCharger;
