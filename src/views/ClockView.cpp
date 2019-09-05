#include "ClockView.h"

#include "log.h"

#include "../utils/format.h"

ClockView::ClockView() : View(Rect((TFT_WIDTH - CLOCK_WIDTH) / 2, 42, CLOCK_WIDTH, CLOCK_HEIGHT)) {
}

unsigned long ClockView::_elapsedSinceLastUpdate() {
  return millis() - _lastUpdateTime;
}

void ClockView::update() {
  if (_elapsedSinceLastUpdate() >= 1000) {
    auto now = DateTime::now();
    if (now > 1000 * 60 * 60) {
      DateTime time(now);
      if (_currentHours != time.hours()) {
        _currentHours = time.hours();
        markAsChanged();
      }
      if (_currentMins != time.minutes()) {
        _currentMins = time.minutes();
        markAsChanged();
      }
      _lastUpdateTime = millis();
    }
  }
}

void ClockView::draw() {
  if (_drawingContext == nullptr) {
    _drawingContext = TFTDrawingContext::createDrawingContext(size(), 1);
    _drawingContext->alloc();
  }
  if (hasChanged()) {
    char timeString[8];
    sprintf(timeString, "%02d : %02d", _currentHours, _currentMins);
    LOG_D("Drawing ClockView %02d:%02d", _currentHours, _currentMins);
    _drawingContext->fill(TFT_BLACK);
    _drawingContext->setTextColor(TFT_WHITE);
    _drawingContext->setFont(7);
    _drawingContext->setFontSize(1);
    _drawingContext->setTextAlign(CC_DATUM);
    _drawingContext->drawString(timeString, bounds().middlePoint());
  }
  _drawingContext->push(frame().origin());
}
