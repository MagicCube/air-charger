#include "ClockView.h"

#include "log.h"

ClockView::ClockView() : View(Rect((TFT_WIDTH - CLOCK_WIDTH) / 2, 42, CLOCK_WIDTH, CLOCK_HEIGHT)) {
}

String ClockView::timeString() {
  return _timeString;
}

void ClockView::timeString(String value) {
  if (!value.equals(_timeString)) {
    _timeString = value;
    markAsChanged();
  }
}

void ClockView::draw() {
  if (_drawingContext == nullptr) {
    _drawingContext = TFTDrawingContext::createDrawingContext(size(), 1);
    _drawingContext->alloc();
  }
  if (hasChanged()) {
    LOG_D("Drawing ClockView %s", _timeString.c_str());
    _drawingContext->fill(TFT_BLACK);
    _drawingContext->setTextColor(TFT_WHITE);
    _drawingContext->setFont(7);
    _drawingContext->setFontSize(1);
    _drawingContext->setTextAlign(CC_DATUM);
    _drawingContext->drawString(_timeString, bounds().middlePoint());
  }
  _drawingContext->push(frame().origin());
}
