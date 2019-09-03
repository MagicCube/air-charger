#pragma once

#include <Arduino.h>

#include <TFT_eSPI.h>

#ifndef NSTARS
#define NSTARS 40
#endif

class StarfieldAnimation {
public:
  StarfieldAnimation(TFT_eSPI *tft);
  void begin();
  void redraw();

private:
  TFT_eSPI *tft;
  uint8_t za, zb, zc, zx;
  uint8_t sx[NSTARS] = {};
  uint8_t sy[NSTARS] = {};
  uint8_t sz[NSTARS] = {};
  unsigned long _lastUpdate = 0;

  void _drawStar(uint8_t x, uint8_t y, uint8_t size, uint32_t color);
  uint8_t _rng();
  int scaleX(uint8_t x, uint8_t z);
  int scaleY(uint8_t y, uint8_t z);
  int scaleZ(uint8_t z);
  int colorScale(uint8_t z);
};
