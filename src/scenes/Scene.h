#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

class Scene {
public:
  virtual bool update(bool forceRedraw) = 0;
  virtual void redraw(TFT_eSPI *canvas) = 0;
};
