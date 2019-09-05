#pragma once

#include <Arduino.h>

#include "../drawing/Point.h"
#include "../drawing/Size.h"

class Bitmap {
public:
  Bitmap(Size size, uint8_t colorDepth);

  Size size();
  uint8_t colorDepth();

  virtual void alloc() = 0;
  virtual void free() = 0;

private:
  Size _size;
  uint8_t _colorDepth;
};
