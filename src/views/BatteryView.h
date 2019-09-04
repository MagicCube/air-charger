#pragma once

#include <Arduino.h>

#include "View.h"

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
};
