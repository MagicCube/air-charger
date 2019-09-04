#pragma once

#include <Arduino.h>

class Scene {
public:
  virtual bool update(bool forceRedraw) = 0;
  virtual void redraw() = 0;
};
