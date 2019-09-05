#include "TFTBitmap.h"

#include "../../displaying/Screen.h"

TFTBitmap::TFTBitmap(Size size, uint8_t p_colorDepth) : Bitmap(size, p_colorDepth) {
  _sprite = new TFT_eSprite(Screen.display());
  _sprite->setColorDepth(colorDepth());
  alloc();
}

TFT_eSprite *TFTBitmap::sprite() {
  return _sprite;
}

TFTDrawingContext *TFTBitmap::createDrawingContext() {
  auto context = new TFTDrawingContext(_sprite, TFTDrawingContextType::SPRITE, size(), colorDepth());
  return context;
}

void TFTBitmap::alloc() {
  _sprite->createSprite(size().width, size().height);
}

void TFTBitmap::free() {
  _sprite->deleteSprite();
}
