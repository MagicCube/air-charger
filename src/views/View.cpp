#include "View.h"

View::View(Rect frame) {
  _frame = frame;
  _bounds = Rect(0, 0, frame.size());
}

Rect View::frame() {
  return _frame;
}

Rect View::bounds() {
  return _bounds;
}

bool View::hasChanged() {
  return _hasChanged;
}

void View::markAsChanged() {
  _hasChanged = true;
  needsRedraw();
}

bool View::needsRedraw() {
  return _needsRedraw;
}

void View::setNeedsRedraw() {
  _needsRedraw = true;
}

void View::redraw(bool force) {
  if (force || needsRedraw()) {
    draw();
  }
  _needsRedraw = false;
  _hasChanged = false;
}

void View::draw() {
}
