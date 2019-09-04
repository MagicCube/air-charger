#include "TFTDrawingContext.h"

#include <typeinfo>

TFTDrawingContext::TFTDrawingContext(TFT_eSPI *tft, TFTDrawingContextType type, Size size,
                                     uint8_t colorDepth) {
  _tft = tft;
  _type = type;
  _size = size;
  _colorDepth = colorDepth;
}

void TFTDrawingContext::commit(Point position) {
  if (_type == TFTDrawingContextType::SPRITE) {
    ((TFT_eSprite *)_tft)->pushSprite(position.x, position.y);
  }
}

void TFTDrawingContext::alloc() {
  if (_type == TFTDrawingContextType::SPRITE) {
    ((TFT_eSprite *)_tft)->createSprite(_size.width, _size.height);
  }
}

void TFTDrawingContext::free() {
  if (_type == TFTDrawingContextType::SPRITE) {
    ((TFT_eSprite *)_tft)->deleteSprite();
  }
}

void TFTDrawingContext::fill(color_t color) {
  if (_type == TFTDrawingContextType::SPRITE) {
    ((TFT_eSprite *)_tft)->fillSprite(color);
  } else {
    _tft->fillScreen(color);
  }
}

Size TFTDrawingContext::size() {
  return Size(_tft->width(), _tft->height());
}

int16_t TFTDrawingContext::width() {
  return _tft->width();
}

int16_t TFTDrawingContext::height() {
  return _tft->height();
}

void TFTDrawingContext::drawPixel(Point position, color_t color) {
  _tft->drawPixel(position.x, position.y, color);
}

void TFTDrawingContext::drawRect(Rect rect, color_t color) {
  _tft->drawRect(rect.left(), rect.top(), rect.width(), rect.height(), color);
}

void TFTDrawingContext::fillRect(Rect rect, color_t color) {
  _tft->fillRect(rect.left(), rect.top(), rect.width(), rect.height(), color);
}

void TFTDrawingContext::drawRoundRect(Rect rect, uint32_t radius, color_t color) {
  if (_type == TFTDrawingContextType::SPRITE) {
    ((TFT_eSprite *)_tft)
        ->drawRoundRect(rect.left(), rect.top(), rect.width(), rect.height(), radius, color);
  } else {
    _tft->drawRoundRect(rect.left(), rect.top(), rect.width(), rect.height(), radius, color);
  }
}

void TFTDrawingContext::fillRoundRect(Rect rect, uint32_t radius, color_t color) {
  _tft->fillRoundRect(rect.left(), rect.top(), rect.width(), rect.height(), radius, color);
}

void TFTDrawingContext::drawCircle(Point position, uint32_t radius, color_t color) {
  _tft->drawCircle(position.x, position.y, radius, color);
}

void TFTDrawingContext::fillCircle(Point position, uint32_t radius, color_t color) {
  _tft->fillCircle(position.x, position.y, radius, color);
}


void TFTDrawingContext::drawXBitmap(x_bitmap_t bitmap, Rect rect, color_t color) {
  _tft->drawXBitmap(rect.left(), rect.top(), bitmap, rect.width(), rect.height(), color);
}


void TFTDrawingContext::setFont(font_t font) {
  _tft->setTextFont(font);
}

void TFTDrawingContext::setFreeFont(const GFXfont *font) {
  _tft->setFreeFont(font);
}

void TFTDrawingContext::setFontSize(font_size_t fontSize) {
  _tft->setTextSize(fontSize);
}

void TFTDrawingContext::setTextColor(color_t color) {
  _tft->setTextColor(color);
}

void TFTDrawingContext::setTextAlign(text_align_t align) {
  _tft->setTextDatum(align);
}

int16_t TFTDrawingContext::drawString(String string, Point position) {
  return _tft->drawString(string, position.x, position.y);
}
