#include "ClockView.h"

#include "../displaying/Screen.h"

ClockView::ClockView() : View(Rect((TFT_WIDTH - 160) / 2, 40, 160, 52)) {
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
    _drawingContext = TFTDrawingContext::createInMemory(Screen.display(), bounds().size(), 1);
    _drawingContext->alloc();
  }
  if (hasChanged()) {
    _drawingContext->fill(TFT_BLACK);
    _drawingContext->setTextColor(TFT_WHITE);
    _drawingContext->setFont(7);
    _drawingContext->setFontSize(1);
    _drawingContext->setTextAlign(CC_DATUM);
    _drawingContext->drawString(_timeString, bounds().middlePoint());
  }
  _drawingContext->commit(frame().origin());
}
