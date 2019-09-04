#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../ble/BLEPeripheral.h"

class ConnectScene : public Scene {
public:
  bool update(bool forceRedraw);
  void redraw();

private:
  BLEPeripheralState _lastState = BLEPeripheralState::INITIALIZING;
};
