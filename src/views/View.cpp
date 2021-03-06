#include "View.h"

View::View(Rect frame) {
  _frame = frame;
  _bounds = Rect(0, 0, _frame.size());
}

Rect View::frame() {
  return _frame;
}

Size View::size() {
  return _bounds.size();
}

Rect View::bounds() {
  return _bounds;
}

bool View::hasChanged() {
  return _hasChanged;
}

bool View::needsRedraw() {
  return _needsRedraw;
}

void View::redraw(bool force) {
  if (force || needsRedraw()) {
    draw();
  }
  _needsRedraw = false;
  _hasChanged = false;
}

void View::markAsChanged() {
  _hasChanged = true;
  needsRedraw();
}

void View::setNeedsRedraw() {
  _needsRedraw = true;
}

void View::update() {
}

void View::draw() {
}
