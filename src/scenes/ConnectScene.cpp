#include "ConnectScene.h"

#include "../drawing/tft/TFTDrawingContext.h"

#include "../resources/bluetooth_logo.h"

void ConnectScene::update() {
  BLEPeripheralState currentState = BLEPeripheral.state();
  if (_lastState != currentState) {
    _lastState = currentState;
    markAsChanged();
  }
}

void ConnectScene::draw() {
  BLEPeripheralState currentState = BLEPeripheral.state();
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

  auto context = TFTDrawingContext::getScreenDrawingContext();
  int32_t screenWidth = context->size().width;
  Screen.clear();
  context->drawXBitmap(
      bluetooth_logo_bits,
      Rect((screenWidth - bluetooth_logo_width) / 2, 40, bluetooth_logo_width, bluetooth_logo_height),
      TFT_BLUE);
  context->setTextColor(TFT_WHITE);
  context->setFont(4);
  context->setFontSize(1);
  context->setTextAlign(CC_DATUM);
  context->drawString(stateStr, Point(screenWidth / 2, 40 + bluetooth_logo_height + 40));
}
