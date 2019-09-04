#pragma once

#include <Arduino.h>

#include "Point.h"
#include "Size.h"

// Stores a set of four egers that represent the location and size of a rectangle.
struct Rect {
public:
  Rect(Point origin, Size size) {
    _origin = origin;
    _size = size;
  }

  Rect(Point origin, int32_t width = 0, int32_t height = 0) {
    _origin = origin;
    _size = Size(width, height);
  }

  Rect(int32_t left, int32_t top, Size size) {
    _origin = Point(left, top);
    _size = size;
  }

  Rect(int32_t left = 0, int32_t top = 0, int32_t width = 0, int32_t height = 0) {
    _origin = Point(left, top);
    _size = Size(width, height);
  }

  Point origin() {
    return _origin;
  }

  Size size() {
    return _size;
  }

  int32_t left() {
    return _origin.x;
  }

  int32_t right() {
    return left() + width();
  }

  int32_t top() {
    return _origin.y;
  }

  int32_t bottom() {
    return top() + height();
  }

  int32_t width() {
    return _size.width;
  }

  int32_t height() {
    return _size.height;
  }

  Point middlePoint() {
    return Point(left() + width() / 2, top() + height() / 2);
  }

private:
  Point _origin;
  Size _size;
};
