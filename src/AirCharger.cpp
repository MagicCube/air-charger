#include "AirCharger.h"

#include <EEPROM.h>

#include "log.h"
#include "settings/Settings.h"

void AirChargerClass::begin(String deviceName) {
  LOG_I("Welcome to AirCharger.");
  LOG_I("Copyright(C) 2019-2020 Henry Li. All rights reserved.");
  AirChargerSettings.begin();
  BLEPeripheral.begin(deviceName);
  if (AirChargerSettings.hasClientAddress()) {
    LOG_I("Running in <SCANNING> mode.");
  } else {
    LOG_I("Running in <PAIRING> mode.");
  }
}

AirChargerClass AirCharger;
