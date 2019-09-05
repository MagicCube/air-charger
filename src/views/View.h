#pragma once

#include <Arduino.h>

#include "../drawing/Rect.h"

class View {
public:
  View(Rect frame);

  Rect frame();
  Rect bounds();
  Size size();

  void redraw(bool force = false);

protected:
  bool needsRedraw();
  void setNeedsRedraw();
  bool hasChanged();
  void markAsChanged();

  virtual void draw() = 0;

private:
  Rect _frame;
  Rect _bounds;
  bool _needsRedraw = true;
  bool _hasChanged = false;
};
