#pragma once

#include <Arduino.h>

#include "View.h"

#include "../drawing/tft/TFTDrawingContext.h"

#define CLOCK_WIDTH 160
#define CLOCK_HEIGHT 52

class ClockView : public View {
public:
  ClockView();

  void update();

protected:
  void draw();

private:
  unsigned long _lastUpdateTime = 0;
  uint8_t _currentHours = 255;
  uint8_t _currentMins = 255;

  TFTDrawingContext *_drawingContext = nullptr;

  unsigned long _elapsedSinceLastUpdate();
};
