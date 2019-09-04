#include "Screen.h"

#include "log.h"

void ScreenClass::begin() {
  _tft.init();
  _tft.setRotation(1);

  showSplash();
}

Rect ScreenClass::bounds() {
  return _bounds;
}

Size ScreenClass::size() {
  return _bounds.size();
}

TFT_eSPI *ScreenClass::display() {
  return &_tft;
}

TFTDrawingContext *ScreenClass::drawingContext() {
  if (_drawingContext == nullptr) {
    _drawingContext = new TFTDrawingContext(&_tft, TFTDrawingContextType::SCREEN, size(), 16);
  }
  return _drawingContext;
}

void ScreenClass::update(bool forceRedraw) {
  Scene *scene = nullptr;
  BLEPeripheralState currentState = BLEPeripheral.state();
  switch (currentState) {
  case BLEPeripheralState::SCANNING:
  case BLEPeripheralState::REMOTE_DEVICE_READY_TO_CONNECT:
  case BLEPeripheralState::REMOTE_DEVICE_CONNECTING:
    if (_connectScene == nullptr) {
      _connectScene = new ConnectScene();
    }
    scene = _connectScene;
    break;
  case BLEPeripheralState::REMOTE_DEVICE_CONNECTED:
    if (_mainScene == nullptr) {
      _mainScene = new MainScene();
    }
    scene = _mainScene;
    break;
  default:
    break;
  }
  if (_currentScene != scene) {
    clear();
    _currentScene = scene;
  }
  if (scene != nullptr) {
    if (scene->update(forceRedraw)) {
      scene->redraw(&_tft);
    }
  }
}

void ScreenClass::clear() {
  _tft.fillScreen(TFT_BLACK);
}

void ScreenClass::showSplash() {
  clear();
  _tft.setTextColor(TFT_WHITE);
  _tft.setFreeFont(&FreeSans18pt7b);
  _tft.setTextSize(1);
  _tft.setTextDatum(CC_DATUM);
  auto middlePoint = bounds().middlePoint();
  _tft.drawString("AirCharger", middlePoint.x, middlePoint.y);
}

void ScreenClass::showMessage(String message) {
  clear();
  _tft.setTextColor(TFT_WHITE);
  _tft.setTextFont(4);
  _tft.setTextSize(1);
  _tft.setTextDatum(CC_DATUM);
  auto middlePoint = bounds().middlePoint();
  _tft.drawString(message, middlePoint.x, middlePoint.y);
}

ScreenClass Screen;
