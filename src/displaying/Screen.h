#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../drawing/Rect.h"

class ScreenClass {
public:
  ScreenClass();

  static ScreenClass *instance();

  void begin();

  Size size();
  Rect bounds();
  TFT_eSPI *display();

  void clear();
  void showSplash();
  void showMessage(String message);

private:
  Rect _bounds = Rect(0, 0, TFT_WIDTH, TFT_HEIGHT);
  TFT_eSPI _tft;
};

extern ScreenClass Screen;
