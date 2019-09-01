#pragma once

#include <Arduino.h>

#include "Scene.h"

class MainScene : public Scene {
public:
  MainScene();
  bool update(bool forceRedraw);
  void redraw(TFT_eSPI *canvas);

private:
  unsigned long _lastRedraw = 0;

  TFT_eSprite *_clock = nullptr;
  Rect _clockFrame;

  void _drawClock(TFT_eSPI *canvas);
};
