#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../animations/StarfieldAnimation.h"
#include "../views/ClockView.h"
#include "../views/BatteryView.h"

class MainScene : public Scene {
public:
  MainScene();
  void update();

protected:
  void draw();

private:
  ClockView _clockView;
  BatteryView _batteryView;
  StarfieldAnimation _animation;
  Rect _chargingIndicatorFrame;

  void _drawChargingIndicator();
};
