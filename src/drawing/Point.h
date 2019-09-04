#pragma once

#include <Arduino.h>

struct Point {
  uint32_t x, y;

  Point(uint32_t p_x = 0, uint32_t p_y = 0) {
    x = p_x;
    y = p_y;
  }
};
