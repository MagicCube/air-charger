#pragma once

#include <Arduino.h>

#include "../conf.h"
#include "../drawing/Rect.h"

#define MAX_STAR_SIZE 5

class StarfieldAnimation {
public:
  StarfieldAnimation();

  void setBlackHoles(Rect blackHole1, Rect blackHole2);

  void redraw();

private:
  uint8_t _za, _zb, _zc, _zx;
  uint8_t sx[NSTARS] = {};
  uint8_t sy[NSTARS] = {};
  uint8_t sz[NSTARS] = {};
  unsigned long _lastUpdate = 0;

  Rect _blackHole1, _blackHole2;

  bool _shouldDrawStar(Point position);
  void _drawStar(Point position, uint8_t z, uint32_t color);
  uint8_t _rng();
  int _xScale(uint8_t x, uint8_t z);
  int _yScale(uint8_t y, uint8_t z);
  int _zScale(uint8_t z);
  int _colorScale(uint8_t z);
};
