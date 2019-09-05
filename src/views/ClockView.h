#pragma once

#include <Arduino.h>

#include "View.h"

#include "../drawing/tft/TFTDrawingContext.h"

#define CLOCK_WIDTH 160
#define CLOCK_HEIGHT 52

class ClockView : public View {
public:
  ClockView();

  String timeString();
  void timeString(String value);

  void update();

protected:
  void draw();

private:
  String _timeString = "-- : --";

  TFTDrawingContext *_drawingContext = nullptr;
};
