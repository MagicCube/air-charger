#pragma once

#include <Arduino.h>

// Stores a set of four egers that represent the location and size of a rectangle.
struct Rect {
  Rect(uint32_t p_left = 0, uint32_t p_top = 0, uint32_t p_width = 0, uint32_t p_height = 0) {
    left = p_left;
    top = p_top;
    width = p_width;
    height = p_height;
  }

  void copyFrom(Rect rect) {
    left = rect.left;
    top = rect.top;
    width = rect.width;
    height = rect.height;
  }

  uint32_t left = 0;
  uint32_t top = 0;
  uint32_t width = 0;
  uint32_t height = 0;
};
