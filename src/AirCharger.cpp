#include "AirCharger.h"

#include <EEPROM.h>

#include "log.h"
#include "utils/format.h"

void AirChargerClass::begin(String deviceName) {
  LOG_I("Welcome to AirCharger.");
  LOG_I("Copyright(C) 2019-2020 Henry Li. All rights reserved.");

  AirChargerSettings.begin();

  Screen.begin();
  if (AirChargerSettings.rebootReason() == AirChargerRebootReason::UNKNOWN) {
    Screen.showSplash();
  }

  BLEPeripheral.setCallbacks(this);
  BLEPeripheral.begin(deviceName);

  if (AirChargerSettings.rebootReason() != AirChargerRebootReason::REPAIR &&
      AirChargerSettings.hasClientAddress()) {
    BLEPeripheral.startScanningMode(AirChargerSettings.clientAddress());
  } else {
    BLEPeripheral.startPairingMode();
  }
  LOG_I("AirCharger is now initialized.");
  LOG_I("================================================================================");
}

uint16_t AirChargerClass::update() {
  auto updateStart = millis();

  _updateScene();
  _updateConnection();

  unsigned long elapsedSinceLastUpdate = millis() - _lastUpdate;
  uint16_t timeBudget = 0;
  if (UPDATE_INTERVAL > elapsedSinceLastUpdate) {
    timeBudget = UPDATE_INTERVAL - elapsedSinceLastUpdate;
  }
  _lastUpdate = updateStart;
  return timeBudget;
}

void AirChargerClass::reboot(AirChargerRebootReason reason, uint16_t after) {
  AirChargerSettings.rebootReason(reason);
  AirChargerSettings.save();
  _readyToReboot = millis() + after;
}

Scene *AirChargerClass::currentScene() {
  return _currentScene;
}

void AirChargerClass::currentScene(Scene *value) {
  if (value != _currentScene) {
    _currentScene = value;
    Screen.clear();
  }
}

void AirChargerClass::_updateScene(bool forceRedraw) {
  Scene *scene = nullptr;
  BLEPeripheralState currentState = BLEPeripheral.state();
  switch (currentState) {
  case BLEPeripheralState::PAIRING:
  case BLEPeripheralState::PAIRED:
    if (_pairingScene == nullptr) {
      _pairingScene = new PairingScene();
    }
    scene = _pairingScene;
    break;
  case BLEPeripheralState::SCANNING:
  case BLEPeripheralState::REMOTE_DEVICE_READY_TO_CONNECT:
  case BLEPeripheralState::REMOTE_DEVICE_CONNECTING:
    if (_connectScene == nullptr) {
      _connectScene = new ConnectScene();
    }
    scene = _connectScene;
    break;
  case BLEPeripheralState::REMOTE_DEVICE_CONNECTED:
    if (_mainScene == nullptr) {
      _mainScene = new MainScene();
    }
    scene = _mainScene;
    break;
  default:
    break;
  }

  if (scene != nullptr) {
    currentScene(scene);
    currentScene()->update();
    currentScene()->redraw(forceRedraw);
  }

  if (_readyToReboot > 0 && millis() >= _readyToReboot) {
    ESP.restart();
  }
}

void AirChargerClass::_updateConnection() {
  if (BLEPeripheral.state() == BLEPeripheralState::REMOTE_DEVICE_READY_TO_CONNECT) {
    BLEPeripheral.connectRemoteDevice(AirChargerSettings.clientAddress());
  } else if (BLEPeripheral.state() == BLEPeripheralState::SCANNING) {
    if (AirChargerSettings.rebootReason() == AirChargerRebootReason::UNKNOWN) {
      if (_suspectNotFound == 0) {
        _suspectNotFound = millis();
        LOG_D("Fail to find device in the very first 3 seconds.");
      }
      if (millis() - _suspectNotFound > 1000 * 7) {
        AirChargerSettings.erase();
        reboot(AirChargerRebootReason::REPAIR);
      }
    }
    BLEPeripheral.continueSearching();
  }
}

void AirChargerClass::onBLEStateChanged() {
  _updateScene(true);
  if (BLEPeripheral.state() == BLEPeripheralState::PAIRED) {
    reboot(AirChargerRebootReason::PAIRED, 5000);
  }
}

void AirChargerClass::onRemoteDeviceConnect() {
}

void AirChargerClass::onRemoteDeviceDisconnect() {
  reboot(AirChargerRebootReason::REMOTE_DEVICE_DISCONNECT);
}

void AirChargerClass::onRemoteDeviceBatteryLevelChanged() {
}

void AirChargerClass::onRemoteDeviceTime(DateTime time) {
  LOG_I("Adjusting current system time [%s, %d]...", formatDateTime(time).c_str(), time.gmtTime());
  DateTime::configTime(time);
}

AirChargerClass AirCharger;
