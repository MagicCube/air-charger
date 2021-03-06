#include "Screen.h"

static ScreenClass *__instance;

#include "conf.h"

ScreenClass::ScreenClass() {
  __instance = this;
}

ScreenClass *ScreenClass::instance() {
  return __instance;
}

void ScreenClass::begin() {
  _tft.init();
  _tft.setRotation(2);
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
  drawConstructionLines();
}

void ScreenClass::drawConstructionLines() {
#ifdef DRAW_CONSTRUCTION_LINES
  _tft.drawCircle(TFT_WIDTH / 2, TFT_WIDTH / 2, TFT_WIDTH / 2 - 1, DRAW_CONSTRUCTION_LINES);
  // _tft.drawRect(0, 0, TFT_WIDTH, TFT_WIDTH, DRAW_CONSTRUCTION_LINES);
#endif
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
