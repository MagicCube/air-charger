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
    LOG_I("Starting in <SCANNING> mode.");
    BLEPeripheral.startParingMode();
  } else {
    LOG_I("Starting in <PAIRING> mode.");
    BLEPeripheral.startParingMode();
  }
  LOG_I("AirCharger is now running in <PAIRING> mode.");
}

AirChargerClass AirCharger;
