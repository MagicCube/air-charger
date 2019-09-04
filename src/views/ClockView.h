#pragma once

#include <Arduino.h>

#include "View.h"

#include "../drawing/tft/TFTDrawingContext.h"

class ClockView : public View {
public:
  ClockView();

  String timeString();
  void timeString(String value);

protected:
  void draw();

private:
  String _timeString = "-- : --";

  TFTDrawingContext *_drawingContext = nullptr;
};
