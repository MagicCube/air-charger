#pragma once

#include <Arduino.h>

#include "ble/BLEPeripheral.h"
#include "charging/Charger.h"
#include "displaying/Screen.h"
#include "settings/Settings.h"

#include "scenes/ConnectScene.h"
#include "scenes/MainScene.h"
#include "scenes/PairingScene.h"

class AirChargerClass : BLEPeripheralCallbacks {
public:
  // Initializes the `AirCharger` with given device name.
  void begin(String deviceName);

  uint16_t update();
  void reboot(AirChargerRebootReason reason, uint16_t after = 0);

  Scene *currentScene();
  void currentScene(Scene *scene);

  // Implements `BLEPeripheralCallbacks`.
  void onBLEStateChanged();
  void onRemoteDeviceConnect();
  void onRemoteDeviceDisconnect();
  void onRemoteDeviceBatteryLevelChanged();
  void onRemoteDeviceTime(DateTime time);

private:
  unsigned long _lastUpdate = 0;
  unsigned long _readyToReboot = 0;
  unsigned long _suspectNotFound = 0;

  Scene *_currentScene = nullptr;
  ConnectScene *_connectScene = nullptr;
  MainScene *_mainScene = nullptr;
  PairingScene *_pairingScene = nullptr;

  void _updateScene(bool forceRedraw = false);
  void _updateConnection();
};

extern AirChargerClass AirCharger;
