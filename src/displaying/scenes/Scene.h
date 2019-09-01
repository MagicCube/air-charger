#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../drawing/Rect.h"

class Scene {
public:
  bool is();
  bool markAsRedraw();
  virtual bool update(bool forceRedraw) = 0;
  virtual void redraw(TFT_eSPI *canvas) = 0;
private:
  bool _isDirty;
};
