#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../ble/BLEPeripheral.h"
#include "../drawing/tft/TFTDrawingContext.h"

#include "../scenes/ConnectScene.h"
#include "../scenes/MainScene.h"

class ScreenClass {
public:
  void begin();

  Size size();
  Rect bounds();
  TFT_eSPI *display();
  TFTDrawingContext *drawingContext();

  void update(bool forceRedraw = false);
  void clear();
  void showSplash();
  void showMessage(String message);

private:
  Rect _bounds = Rect(0, 0, TFT_WIDTH, TFT_HEIGHT);
  TFT_eSPI _tft;
  TFTDrawingContext *_drawingContext = nullptr;
  Scene *_currentScene = nullptr;
  ConnectScene *_connectScene = nullptr;
  MainScene *_mainScene = nullptr;
};

extern ScreenClass Screen;
