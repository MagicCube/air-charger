#include "StarfieldAnimation.h"

#define TFT_HALF_WIDTH TFT_WIDTH / 2
#define TFT_HALF_HEIGHT TFT_HEIGHT / 2

StarfieldAnimation::StarfieldAnimation(TFT_eSPI *pTFT) {
  tft = pTFT;
}

void StarfieldAnimation::begin() {
  za = random(256);
  zb = random(256);
  zc = random(256);
  zx = random(256);
}

void StarfieldAnimation::redraw() {
  uint8_t spawnDepthVariation = 255;

  for (uint8_t i = 0; i < NSTARS; ++i) {
    if (sz[i] <= 1) {
      sx[i] = TFT_HALF_WIDTH - TFT_HALF_HEIGHT + _rng();
      sy[i] = _rng();
      sz[i] = spawnDepthVariation--;
    } else {
      int last_x = scaleX(sx[i], sz[i]);
      int last_y = scaleX(sy[i], sz[i]);
      int last_z = scaleZ(sz[i]);

      // This is a faster pixel drawing function for occassions where many single pixels must be
      // drawn
      _drawStar(last_x, last_y, last_z, TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1) {
        int x = scaleX(sx[i], sz[i]);
        int y = scaleX(sy[i], sz[i]);
        int z = scaleZ(sz[i]);

        if (x >= 0 && y >= 0 && x < TFT_WIDTH && y < TFT_HEIGHT) {
          _drawStar(x, y, z, colorScale(sz[i]));
        } else {
          sz[i] = 0; // Out of screen, die.
        }
      }
    }
  }
}

void StarfieldAnimation::_drawStar(uint8_t x, uint8_t y, uint8_t size, uint32_t color) {
  tft->fillCircle(x, y, size, color);
}

uint8_t StarfieldAnimation::_rng() {
  zx++;
  za = (za ^ zc ^ zx);
  zb = (zb + za);
  zc = zc + ((zb >> 1) ^ za);
  return zc;
}

int StarfieldAnimation::scaleX(uint8_t x, uint8_t z) {
  return ((int)x - TFT_HALF_WIDTH) * 256 / z + TFT_HALF_WIDTH;
}

int StarfieldAnimation::scaleY(uint8_t y, uint8_t z) {
  return ((int)y - TFT_HALF_HEIGHT) * 256 / z + TFT_HALF_HEIGHT;
}

int StarfieldAnimation::scaleZ(uint8_t z) {
  return 5 - z / 85;
}

int StarfieldAnimation::colorScale(uint8_t z) {
  uint8_t r, g, b;
  r = g = b = 255 - z;
  return tft->color565(r, g, b);
}
