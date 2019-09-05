#pragma once

#include <Arduino.h>

#include "../Bitmap.h"

#include "./TFTDrawingContext.h"

class TFTBitmap : public Bitmap {
public:
  TFTBitmap(Size size, uint8_t colorDepth);

  TFT_eSprite *sprite();

  TFTDrawingContext *createDrawingContext();
  void alloc();
  void free();

private:
  TFT_eSprite *_sprite;
};
