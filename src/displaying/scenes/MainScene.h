#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../../animations/StarfieldAnimation.h"
#include "../../drawing/tft/TFTDrawingContext.h"

#include "../../views/ClockView.h"
#include "../../views/BatteryView.h"

class MainScene : public Scene {
public:
  bool update(bool forceRedraw);
  void redraw(TFT_eSPI *canvas);

private:
  unsigned long _lastRedraw = 0;

  ClockView *_clockView = nullptr;
  BatteryView *_batteryView = nullptr;

  StarfieldAnimation *_animation = nullptr;

  void _drawBackground();
  void _drawClock();
  void _drawBattery();
  void _drawChargingIndicator();
};
