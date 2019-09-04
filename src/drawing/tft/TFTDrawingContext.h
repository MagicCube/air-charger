#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../DrawingContext.h"

enum class TFTDrawingContextType {
  SCREEN,
  SPRITE
};

class TFTDrawingContext : public DrawingContext {
public:
  TFTDrawingContext(TFT_eSPI *tft, TFTDrawingContextType type, Size size = Size(TFT_WIDTH, TFT_HEIGHT), uint8_t colorDepth = 16);

  static TFTDrawingContext *createInMemory(TFT_eSPI *tft, Size size, uint8_t colorDepth = 16) {
    TFT_eSprite *sprite = new TFT_eSprite(tft);
    sprite->setColorDepth(colorDepth);
    auto context = new TFTDrawingContext(sprite, TFTDrawingContextType::SPRITE, size);
    return context;
  }

  // Size
  Size size();
  int16_t width();
  int16_t height();

  // Lifecycle
  void alloc();
  void free();
  void commit(Point position);

  // Basic
  void fill(color_t color);
  void drawPixel(Point position, color_t color);
  void drawRect(Rect rect, color_t color);
  void fillRect(Rect rect, color_t color);
  void drawRoundRect(Rect rect, uint32_t radius, color_t color);
  void fillRoundRect(Rect rect, uint32_t radius, color_t color);
  void drawCircle(Point position, uint32_t radius, color_t color);
  void fillCircle(Point position, uint32_t radius, color_t color);

  // Image
  void drawXBitmap(x_bitmap_t bitmap, Rect rect, color_t color);

  // Text
  void setFont(font_t font);
  void setFreeFont(const GFXfont *font);
  void setFontSize(font_size_t fontSize);
  void setTextColor(color_t color);
  void setTextAlign(text_align_t align);
  int16_t drawString(String string, Point position);

private:
  TFT_eSPI *_tft;
  TFTDrawingContextType _type;
  uint8_t _colorDepth;
  Size _size;
};
