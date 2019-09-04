#pragma once

#include <Arduino.h>

struct Size {
  uint32_t width, height;

  Size(uint32_t p_width = 0, uint32_t p_height = 0) {
    width = p_width;
    height = p_height;
  }
};
