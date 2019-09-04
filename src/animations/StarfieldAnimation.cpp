#include "StarfieldAnimation.h"

#include "../displaying/Screen.h"

StarfieldAnimation::StarfieldAnimation() {
  _za = random(256);
  _zb = random(256);
  _zc = random(256);
  _zx = random(256);
}

void StarfieldAnimation::redraw() {
  uint8_t spawnDepthVariation = 255;

  for (uint8_t i = 0; i < NSTARS; ++i) {
    if (sz[i] <= 1) {
      sx[i] = TFT_WIDTH / 2 - TFT_HEIGHT / 2 + _rng();
      sy[i] = _rng();
      sz[i] = spawnDepthVariation--;
    } else {
      int last_x = _xScale(sx[i], sz[i]);
      int last_y = _yScale(sy[i], sz[i]);

      // This is a faster pixel drawing function for occassions where many single pixels must be
      // drawn
      _drawStar(last_x, last_y, sz[i], TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1) {
        int x = _xScale(sx[i], sz[i]);
        int y = _yScale(sy[i], sz[i]);

        if (_shouldDrawStar(x, y)) {
          _drawStar(x, y, sz[i], _colorScale(sz[i]));
        } else {
          sz[i] = 0; // Out of screen, die.
        }
      }
    }
  }
}

bool StarfieldAnimation::_shouldDrawStar(int x, int y) {
  if (x >= 0 && y >= 0 && x < TFT_WIDTH && y < TFT_HEIGHT) {
    return true;
  }
  return false;
}

void StarfieldAnimation::_drawStar(uint8_t x, uint8_t y, uint8_t z, uint32_t color) {
  auto context = Screen.drawingContext();
  context->fillCircle(Point(x, y), _zScale(z), color);
}

uint8_t StarfieldAnimation::_rng() {
  _zx++;
  _za = (_za ^ _zc ^ _zx);
  _zb = (_zb + _za);
  _zc = _zc + ((_zb >> 1) ^ _za);
  return _zc;
}

int StarfieldAnimation::_xScale(uint8_t x, uint8_t z) {
  return ((int)x - TFT_WIDTH / 2) * 256 / z + TFT_WIDTH / 2;
}

int StarfieldAnimation::_yScale(uint8_t y, uint8_t z) {
  return ((int)y - TFT_HEIGHT / 2) * 256 / z + TFT_HEIGHT / 2;
}

int StarfieldAnimation::_zScale(uint8_t z) {
  return MAX_STAR_SIZE - z / 85;
}

int StarfieldAnimation::_colorScale(uint8_t z) {
  uint8_t r, g, b;
  r = g = b = 255 - z;
  return color565(r, g, b);
}
