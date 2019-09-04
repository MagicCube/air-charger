#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../ble/BLEPeripheral.h"

class ConnectScene : public Scene {
public:
  bool update(bool forceRedraw);
  void redraw(TFT_eSPI *canvas);

private:
  BLEPeripheralState _lastState = BLEPeripheralState::INITIALIZING;
};
