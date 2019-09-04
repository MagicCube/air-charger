#pragma once

#include <Arduino.h>

#include "../drawing/tft/TFTDrawingContext.h"

class View {
public:
  View(Rect frame);

  Rect frame();
  Rect bounds();

  void redraw(bool force = false);

protected:
  bool needsRedraw();
  void setNeedsRedraw();
  bool hasChanged();
  void markAsChanged();
  unsigned long lastRedrawTime();
  unsigned long elapsedSinceLastRedraw();

  virtual void draw() = 0;

private:
  Rect _frame;
  Rect _bounds;
  bool _needsRedraw = true;
  bool _hasChanged = false;
  unsigned long _lastRedrawTime = 0;
};