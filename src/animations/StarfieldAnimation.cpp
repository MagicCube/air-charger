#include "StarfieldAnimation.h"

#include "../displaying/Screen.h"

#define BLACK_HOLE_SPACING 3

StarfieldAnimation::StarfieldAnimation() {
  _za = random(256);
  _zb = random(256);
  _zc = random(256);
  _zx = random(256);
}

void StarfieldAnimation::setBlackHole(Rect value) {
  _blackHole =
      Rect(value.left() - BLACK_HOLE_SPACING, value.top() - BLACK_HOLE_SPACING,
           value.width() + BLACK_HOLE_SPACING * 2, value.height() + BLACK_HOLE_SPACING * 2);
}

void StarfieldAnimation::redraw() {
  uint8_t spawnDepthVariation = 255;

  for (uint8_t i = 0; i < NSTARS; ++i) {
    if (sz[i] <= 1) {
      sx[i] = Screen.size().width / 2 - Screen.size().height / 2 + _rng();
      sy[i] = _rng();
      sz[i] = spawnDepthVariation--;
    } else {
      int last_x = _xScale(sx[i], sz[i]);
      int last_y = _yScale(sy[i], sz[i]);
      Point point(last_x, last_y);

      // This is a faster pixel drawing function for occassions where many single pixels must be
      // drawn
      _drawStar(point, sz[i], TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1) {
        int x = _xScale(sx[i], sz[i]);
        int y = _yScale(sy[i], sz[i]);
        Point point(x, y);

        if (_shouldDrawStar(point)) {
          _drawStar(point, sz[i], _colorScale(sz[i]));
        } else {
          sz[i] = 0; // Out of screen, die.
        }
      }
    }
  }
}

bool StarfieldAnimation::_shouldDrawStar(Point position) {
  if (Screen.bounds().contains(position)) {
    return !_blackHole.contains(position);
  }
  return false;
}

void StarfieldAnimation::_drawStar(Point position, uint8_t z, uint32_t color) {
  auto context = Screen.drawingContext();
  context->fillCircle(position, _zScale(z), color);
}

uint8_t StarfieldAnimation::_rng() {
  _zx++;
  _za = (_za ^ _zc ^ _zx);
  _zb = (_zb + _za);
  _zc = _zc + ((_zb >> 1) ^ _za);
  return _zc;
}

int StarfieldAnimation::_xScale(uint8_t x, uint8_t z) {
  return ((int)x - Screen.size().width / 2) * 256 / z + Screen.size().width / 2;
}

int StarfieldAnimation::_yScale(uint8_t y, uint8_t z) {
  return ((int)y - Screen.size().height / 2) * 256 / z + Screen.size().height / 2;
}

int StarfieldAnimation::_zScale(uint8_t z) {
  return MAX_STAR_SIZE - z / 85;
}

int StarfieldAnimation::_colorScale(uint8_t z) {
  uint8_t r, g, b;
  r = g = b = 255 - z;
  return color565(r, g, b);
}
