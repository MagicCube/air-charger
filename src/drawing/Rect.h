#pragma once

#include <Arduino.h>

// Stores a set of four egers that represent the location and size of a rectangle.
struct Rect {
public:
  Rect(uint32_t left = 0, uint32_t top = 0, uint32_t width = 0, uint32_t height = 0) {
    _left = left;
    _top = top;
    _width = width;
    _height = height;
  }

  uint32_t left() {
    return _left;
  }

  uint32_t top() {
    return _top;
  }

  uint32_t width() {
    return _width;
  }

  uint32_t height() {
    return _height;
  }

  void copyFrom(Rect rect) {
    _left = rect.left();
    _top = rect.top();
    _width = rect.width();
    _height = rect.height();
  }

private:
  uint32_t _left = 0;
  uint32_t _top = 0;
  uint32_t _width = 0;
  uint32_t _height = 0;
};
