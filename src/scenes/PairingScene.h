#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../ble/BLEPeripheral.h"

class PairingScene : public Scene {
public:
  void update();

protected:
  void draw();

private:
  BLEPeripheralState _lastState = BLEPeripheralState::INITIALIZING;
};
