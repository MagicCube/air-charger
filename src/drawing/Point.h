#pragma once

#include <Arduino.h>

struct Point {
  int32_t x, y;

  Point(int32_t p_x = 0, int32_t p_y = 0) {
    x = p_x;
    y = p_y;
  }
};
