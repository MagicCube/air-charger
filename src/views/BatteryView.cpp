#include "BatteryView.h"

#define TFT_GREY 0x4208

#include "log.h"

#include "../utils/format.h"

BatteryView::BatteryView()
    : View(Rect((TFT_WIDTH - BATTERY_WIDTH) / 2 + BATTERY_HEAD_WIDTH / 2, 128, BATTERY_WIDTH,
                BATTERY_HEIGHT)) {
}

uint8_t BatteryView::batteryLevel() {
  return _batteryLevel;
}
void BatteryView::batteryLevel(uint8_t value) {
  if (_batteryLevel != value) {
    _batteryLevel = value;
    markAsChanged();
  }
}

bool BatteryView::isCharging() {
  return _isCharging;
}
void BatteryView::isCharging(bool value) {
  if (_isCharging != value) {
    _isCharging = value;
    markAsChanged();
  }
}

void BatteryView::draw() {
  if (_drawingContext == nullptr) {
    _drawingContext = TFTDrawingContext::createDrawingContext(size(), 8);
    _drawingContext->alloc();
    _drawOutline();
    _drawHead();
  }
  if (hasChanged()) {
    LOG_D("Drawing BatteryView %d%%", _batteryLevel);
    _drawBody();
  }
  _drawingContext->push(frame().origin());
}

void BatteryView::_drawHead() {
  int headHeight = size().height / 2;
  _drawingContext->fillRoundRect(Rect(size().width - BATTERY_HEAD_WIDTH,
                                      (size().height - headHeight) / 2, BATTERY_HEAD_WIDTH,
                                      headHeight),
                                 BATTERY_ROUNDNESS, TFT_WHITE);
}

void BatteryView::_drawOutline() {
  _drawingContext->drawRoundRect(Rect(0, 0, size().width - BATTERY_HEAD_WIDTH - 3, size().height),
                                 BATTERY_HEAD_WIDTH, TFT_WHITE);
}

void BatteryView::_drawBody() {
  int batteryWidth = ((float)(size().width - BATTERY_HEAD_WIDTH - BATTERY_PADDING * 2 - 3));
  int innerBatteryWidth = batteryWidth * ((float)_batteryLevel / 100);
  auto batteryColor = TFT_DARKGREEN;
  if (_batteryLevel <= 10) {
    batteryColor = TFT_RED;
  } else if (_batteryLevel <= 20) {
    batteryColor = TFT_ORANGE;
  }
  // Clear
  _drawingContext->fillRect(
      Rect(BATTERY_PADDING, BATTERY_PADDING, batteryWidth, size().height - BATTERY_PADDING * 2),
      TFT_BLACK);
  // Fill
  _drawingContext->fillRect(Rect(BATTERY_PADDING, BATTERY_PADDING, innerBatteryWidth,
                                 size().height - BATTERY_PADDING * 2),
                            batteryColor);
  // Draw text
  _drawPercentage();
}

void BatteryView::_drawPercentage() {
  _drawingContext->setTextColor(TFT_WHITE);
  _drawingContext->setFreeFont(&FreeSansBold18pt7b);
  _drawingContext->setFontSize(1);
  _drawingContext->setTextAlign(CC_DATUM);
  _drawingContext->drawString(
      formatPercentage(_batteryLevel),
      Point((size().width - BATTERY_HEAD_WIDTH - 3) / 2, size().height / 2));
}
