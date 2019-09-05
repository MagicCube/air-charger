#include "Bitmap.h"

Bitmap::Bitmap(Size size, uint8_t colorDepth) {
  _size = size;
  _colorDepth = colorDepth;
}

Size Bitmap::size() {
  return _size;
}

uint8_t Bitmap::colorDepth() {
  return _colorDepth;
}
