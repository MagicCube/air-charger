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

  BLEPeripheral.setCallbacks(this);
  BLEPeripheral.begin(deviceName);

  if (AirChargerSettings.hasClientAddress()) {
    drawMessage("Scanning...");
    BLEPeripheral.startScanningMode(AirChargerSettings.getClientAddress());
  } else {
    BLEPeripheral.startParingMode();
  }
  LOG_I("AirCharger is now initialized.");
  LOG_I("================================================================================");
}

void AirChargerClass::update() {
  if (BLEPeripheral.state() == BLEPeripheralState::REMOTE_DEVICE_READY_TO_CONNECT) {
    drawMessage("Connecting...");
    BLEPeripheral.connectRemoteDevice(AirChargerSettings.getClientAddress());
    redraw();
  }
}

void AirChargerClass::redraw() {
  _display.fillScreen(TFT_BLACK);

  _display.setTextColor(TFT_DARKGREY);
  _display.setFreeFont(&FreeSans12pt7b);
  _display.setTextSize(1);
  _display.setTextDatum(TC_DATUM);
  auto percentage = String("Charging ") + BLEPeripheral.getRemoteDevice()->batteryLevel() + "%";
  _display.drawString(percentage, TFT_WIDTH / 2, 32);

  _display.setTextColor(TFT_WHITE);
  _display.setTextFont(7);
  _display.setTextSize(1);
  _display.setTextDatum(BC_DATUM);

  DateTime dateTime(DateTime::now());
  char dateStr[6];
  sprintf(dateStr, "%.2d:%.2d", (dateTime.getHours() + TIME_ZONE_OFFSET / 60) % 24, dateTime.getMinutes());
  _display.drawString(dateStr, TFT_WIDTH / 2, TFT_HEIGHT - 32);
}

void AirChargerClass::drawMessage(String message) {
  _display.fillScreen(TFT_BLACK);

  _display.setTextColor(TFT_WHITE);
  _display.setTextFont(4);
  _display.setTextSize(1);
  _display.setTextDatum(CC_DATUM);
  _display.drawString(message, TFT_WIDTH / 2, TFT_HEIGHT / 2);
}

void AirChargerClass::onRemoteDeviceConnect() {
}

void AirChargerClass::onRemoteDeviceDisconnect() {
  ESP.restart();
}

void AirChargerClass::onRemoteDeviceBatteryLevelChanged() {
  redraw();
}

void AirChargerClass::onRemoteDeviceTime(DateTime time) {
  LOG_I("Adjusting current system time [%d-%d-%d %2.d:%2.d:%2.d, %d]...", time.getFullYear(),
        time.getMonth() + 1, time.getDate(), time.getHours(), time.getMinutes(), time.getSeconds(), time.gmtTime());
  DateTime::configTime(time);
}

AirChargerClass AirCharger;
