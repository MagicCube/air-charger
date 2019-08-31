#include "AirCharger.h"

#include <EEPROM.h>

#include "log.h"
#include "settings/Settings.h"

void AirChargerClass::begin(String deviceName) {
  LOG_I("Welcome to AirCharger.");
  LOG_I("Copyright(C) 2019-2020 Henry Li. All rights reserved.");

  _display.init();
  _display.setRotation(1);
  _display.fillScreen(TFT_BLACK);

  AirChargerSettings.begin();
  BLEPeripheral.begin(deviceName);
  if (AirChargerSettings.hasClientAddress()) {
    BLEPeripheral.startScanningMode(AirChargerSettings.getClientAddress());
    // BLEPeripheral.startParingMode();
  } else {
    BLEPeripheral.startParingMode();
  }
  LOG_I("AirCharger is now initialized.");
  LOG_I("================================================================================");
}

void AirChargerClass::update() {
  if (BLEPeripheral.state() == BLEPeripheralState::READY_TO_CONNECT) {
    BLEPeripheral.connect(AirChargerSettings.getClientAddress());
    redraw();
  }
}

void AirChargerClass::redraw() {
  _display.fillScreen(TFT_BLACK);
  _display.setTextFont(7);
  _display.setTextSize(1);
  _display.setTextColor(TFT_WHITE);
  _display.setTextDatum(CC_DATUM);
  _display.drawNumber(BLEPeripheral.getRemoteDevice()->batteryLevel(), TFT_WIDTH / 2,
                      TFT_HEIGHT / 2);
}

AirChargerClass AirCharger;
