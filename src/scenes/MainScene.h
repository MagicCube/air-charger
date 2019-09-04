#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../animations/StarfieldAnimation.h"
#include "../drawing/tft/TFTDrawingContext.h"

#include "../views/ClockView.h"
#include "../views/BatteryView.h"

class MainScene : public Scene {
public:
  MainScene();
  bool update(bool forceRedraw);
  void redraw(TFT_eSPI *canvas);

private:
  ClockView _clockView;
  BatteryView _batteryView;
  StarfieldAnimation _animation;
  Rect _chargingIndicatorFrame;

  void _drawChargingIndicator();
};
