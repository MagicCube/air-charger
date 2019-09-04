#include "AirCharger.h"

#include <EEPROM.h>

#include "log.h"
#include "utils/format.h"

void AirChargerClass::begin(String deviceName) {
  LOG_I("Welcome to AirCharger.");
  LOG_I("Copyright(C) 2019-2020 Henry Li. All rights reserved.");

  AirChargerSettings.begin();

  BLEPeripheral.setCallbacks(this);
  BLEPeripheral.begin(deviceName);

  if (AirChargerSettings.hasClientAddress()) {
    BLEPeripheral.startScanningMode(AirChargerSettings.clientAddress());
  } else {
    Display.showMessage("Paring...");
    Display.showMessage(DEVICE_NAME);
    BLEPeripheral.startParingMode();
  }
  LOG_I("AirCharger is now initialized.");
  LOG_I("================================================================================");
}

uint16_t AirChargerClass::update() {
  auto updateStart = millis();

  Display.update();
  _checkConnection();

  unsigned long elapsedSinceLastUpdate = millis() - _lastUpdate;
  uint16_t timeBudget = 0;
  if (UPDATE_INTERVAL > elapsedSinceLastUpdate) {
    timeBudget = UPDATE_INTERVAL - elapsedSinceLastUpdate;
  }
  _lastUpdate = updateStart;
  return timeBudget;
}

void AirChargerClass::_checkConnection() {
  if (BLEPeripheral.state() == BLEPeripheralState::REMOTE_DEVICE_READY_TO_CONNECT) {
    BLEPeripheral.connectRemoteDevice(AirChargerSettings.clientAddress());
  } else if (BLEPeripheral.state() == BLEPeripheralState::SCANNING) {
    BLEPeripheral.continueSearching();
  }
}

void AirChargerClass::onStateChanged() {
  Display.update(true);
}

void AirChargerClass::onRemoteDeviceConnect() {
}

void AirChargerClass::onRemoteDeviceDisconnect() {
  Display.showSplash();
  ESP.restart();
}

void AirChargerClass::onRemoteDeviceBatteryLevelChanged() {
  Display.update(true);
}

void AirChargerClass::onRemoteDeviceTime(DateTime time) {
  LOG_I("Adjusting current system time [%s, %d]...", formatDateTime(time).c_str(), time.gmtTime());
  DateTime::configTime(time);
}

AirChargerClass AirCharger;
