#pragma once

#include <Arduino.h>

#include "colors.h"
#include "types.h"

#include "Point.h"
#include "Rect.h"
#include "Size.h"

class DrawingContext {
public:
  // Lifecycle
  virtual void alloc() = 0;
  virtual void free() = 0;
  virtual void commit(Point position) = 0;

  // Basic
  virtual void fill(color_t color) = 0;
  virtual void drawPixel(Point position, color_t color);
  virtual void drawRect(Rect rect, color_t color);
  virtual void fillRect(Rect rect, color_t color);
  virtual void drawRoundRect(Rect rect, uint32_t radius, color_t color);
  virtual void fillRoundRect(Rect rect, uint32_t radius, color_t color);
  virtual void drawCircle(Point position, uint32_t radius, color_t color);
  virtual void fillCircle(Point position, uint32_t radius, color_t color);

  // Image
  virtual void drawXBitmap(x_bitmap_t image, Rect rect, color_t color);

  // Text
  virtual void setFont(font_t font) = 0;
  virtual void setFontSize(font_size_t fontSize) = 0;
  virtual void setTextColor(color_t color) = 0;
  virtual void setTextAlign(text_align_t align) = 0;
  virtual int16_t drawString(String string, Point position) = 0;
};
