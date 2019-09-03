#pragma once

#include <Arduino.h>

#include "Scene.h"

#include "../../animations/StarfieldAnimation.h"

class MainScene : public Scene {
public:
  MainScene();
  bool update(bool forceRedraw);
  void redraw(TFT_eSPI *canvas);

private:
  unsigned long _lastRedraw = 0;

  TFT_eSprite *_clock = nullptr;
  Rect _clockFrame;

  TFT_eSprite *_battery = nullptr;
  Rect _batteryFrame;

  Rect _chargingIndicatorFrame;

  StarfieldAnimation *_animation = nullptr;

  void _drawBackground(TFT_eSPI *canvas);
  void _drawClock(TFT_eSPI *canvas);
  void _drawBattery(TFT_eSPI *canvas);
  void _drawChargingIndicator(TFT_eSPI *canvas);
};
