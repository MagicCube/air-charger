#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../ble/BLEPeripheral.h"
#include "../drawing/tft/TFTDrawingContext.h"

#include "scenes/ConnectScene.h"
#include "scenes/MainScene.h"

class ScreenClass {
public:
  void begin();

  TFT_eSPI *display();
  TFTDrawingContext *screenDrawingContext();

  void update(bool forceRedraw = false);
  void clear();
  void showSplash();
  void showMessage(String message);

private:
  TFT_eSPI _tft;
  TFTDrawingContext *_screenDrawingContext = nullptr;
  Scene *_currentScene = nullptr;
  ConnectScene *_connectScene = nullptr;
  MainScene *_mainScene = nullptr;
};

extern ScreenClass Screen;
