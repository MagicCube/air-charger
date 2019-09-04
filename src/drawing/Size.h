#pragma once

#include <Arduino.h>

struct Size {
  int32_t width, height;

  Size(int32_t p_width = 0, int32_t p_height = 0) {
    width = p_width;
    height = p_height;
  }
};
