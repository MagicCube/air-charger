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

  Rect(Point origin, uint32_t width = 0, uint32_t height = 0) {
    _origin = origin;
    _size = Size(width, height);
  }

  Rect(uint32_t left, uint32_t top, Size size) {
    _origin = Point(left, top);
    _size = size;
  }

  Rect(uint32_t left = 0, uint32_t top = 0, uint32_t width = 0, uint32_t height = 0) {
    _origin = Point(left, top);
    _size = Size(width, height);
  }

  Point origin() {
    return _origin;
  }

  Size size() {
    return _size;
  }

  uint32_t left() {
    return _origin.x;
  }

  uint32_t right() {
    return _origin.x + _size.width;
  }

  uint32_t top() {
    return _origin.y;
  }

  uint32_t bottom() {
    return _origin.y + _size.height;
  }

  uint32_t width() {
    return _origin.y;
  }

  uint32_t height() {
    return _origin.y + _size.height;
  }

private:
  Point _origin;
  Size _size;
};
