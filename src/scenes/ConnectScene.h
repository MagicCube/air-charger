#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../ble/BLEPeripheral.h"

class ConnectScene : public Scene {
public:
  void update();

protected:
  void draw();

private:
  BLEPeripheralState _lastState = BLEPeripheralState::INITIALIZING;
};
