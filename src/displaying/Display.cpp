#include "Display.h"

#include "log.h"

void DisplayClass::begin() {
  _tft.init();
  _tft.setRotation(1);
  _tft.fillScreen(TFT_BLACK);

  _tft.setTextColor(TFT_WHITE);
  _tft.setFreeFont(&FreeSans18pt7b);
  _tft.setTextSize(1);
  _tft.setTextDatum(CC_DATUM);
  _tft.drawString("AirCharger", TFT_WIDTH / 2, TFT_HEIGHT / 2);
}

TFT_eSPI DisplayClass::canvas() {
  return _tft;
}

void DisplayClass::update(bool forceRedraw) {
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
  if (scene != nullptr) {
    if (scene->update(forceRedraw)) {
      scene->redraw(&_tft);
    }
  }
}

void DisplayClass::showMessage(String message) {
  _tft.fillScreen(TFT_BLACK);
  _tft.setTextColor(TFT_WHITE);
  _tft.setTextFont(4);
  _tft.setTextSize(1);
  _tft.setTextDatum(CC_DATUM);
  _tft.drawString(message, TFT_WIDTH / 2, TFT_HEIGHT / 2);
}

DisplayClass Display;
