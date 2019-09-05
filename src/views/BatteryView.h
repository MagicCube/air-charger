#pragma once

#include <Arduino.h>

#include "View.h"

#include "../drawing/tft/TFTDrawingContext.h"

#define BATTERY_WIDTH 150
#define BATTERY_HEIGHT 60
#define BATTERY_HEAD_WIDTH 6
#define BATTERY_ROUNDNESS 4
#define BATTERY_PADDING 5

class BatteryView : public View {
public:
  BatteryView();

  uint8_t batteryLevel();
  void batteryLevel(uint8_t value);
  bool isCharging();
  void isCharging(bool isCharging);

protected:
  void draw();

private:
  uint8_t _batteryLevel = 0;
  bool _isCharging = false;

  TFTDrawingContext *_drawingContext = nullptr;

  void _drawHead();
  void _drawOutline();
  void _drawBody();
  void _drawPercentage();
};
