#include "Screen.h"

static ScreenClass *__instance;

ScreenClass::ScreenClass() {
  __instance = this;
}

ScreenClass *ScreenClass::instance() {
  return __instance;
}

void ScreenClass::begin() {
  _tft.init();
  _tft.setRotation(1);

  showSplash();
}

Rect ScreenClass::bounds() {
  return _bounds;
}

Size ScreenClass::size() {
  return _bounds.size();
}

TFT_eSPI *ScreenClass::display() {
  return &_tft;
}

void ScreenClass::clear() {
  _tft.fillScreen(TFT_BLACK);
  auto s = size();
  _tft.drawCircle(s.width / 2, s.height / 2, s.width / 2, TFT_RED);
}

void ScreenClass::showSplash() {
  clear();
  _tft.setTextColor(TFT_WHITE);
  _tft.setFreeFont(&FreeSans18pt7b);
  _tft.setTextSize(1);
  _tft.setTextDatum(CC_DATUM);
  auto middlePoint = bounds().middlePoint();
  _tft.drawString("AirCharger", middlePoint.x, middlePoint.y);
}

void ScreenClass::showMessage(String message) {
  clear();
  _tft.setTextColor(TFT_WHITE);
  _tft.setTextFont(4);
  _tft.setTextSize(1);
  _tft.setTextDatum(CC_DATUM);
  auto middlePoint = bounds().middlePoint();
  _tft.drawString(message, middlePoint.x, middlePoint.y);
}

ScreenClass Screen;
