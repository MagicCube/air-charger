#include "ConnectScene.h"

#include "../drawing/tft/TFTDrawingContext.h"

#include "../resources/bluetooth_logo.h"

void ConnectScene::update() {
  BLEPeripheralState currentState = BLEPeripheral.state();
  if (_lastState != currentState) {
    _lastState = currentState;
    _lastStateChangedTime = millis();
    _hibernate = false;
    markAsChanged();
  } else {
    if (!_hibernate && currentState == BLEPeripheralState::SCANNING &&
        millis() - _lastStateChangedTime > 3 * 60 * 1000) {
      _hibernate = true;
      setNeedsRedraw();
    }
  }
}

void ConnectScene::draw() {
  BLEPeripheralState currentState = BLEPeripheral.state();

  if (_hibernate) {
    Screen.clear();
  } else {
    String stateStr;
    switch (currentState) {
    case BLEPeripheralState::SCANNING:
      stateStr = "Scanning...";
      break;
    case BLEPeripheralState::REMOTE_DEVICE_READY_TO_CONNECT:
    case BLEPeripheralState::REMOTE_DEVICE_CONNECTING:
      stateStr = "Connecting...";
      break;
    default:
      break;
    }
    Screen.clear();
    auto context = TFTDrawingContext::getScreenDrawingContext();
    context->setTextColor(TFT_WHITE);
    context->setTextAlign(CC_DATUM);
    context->setFontSize(1);
    int32_t screenWidth = context->size().width;
    context->drawXBitmap(bluetooth_logo_bits,
                         Rect((screenWidth - bluetooth_logo_width) / 2, 40, bluetooth_logo_width,
                              bluetooth_logo_height),
                         color565(0, 130, 252));
    context->setFont(4);
    context->drawString(stateStr, Point(screenWidth / 2, 40 + bluetooth_logo_height + 40));
  }
}
