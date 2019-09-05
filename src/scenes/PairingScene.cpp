#include "PairingScene.h"

#include "../drawing/tft/TFTDrawingContext.h"

#include "../resources/bluetooth_logo.h"

void PairingScene::update() {
  BLEPeripheralState currentState = BLEPeripheral.state();
  if (_lastState != currentState) {
    _lastState = currentState;
    markAsChanged();
  }
}

void PairingScene::draw() {
  BLEPeripheralState currentState = BLEPeripheral.state();
  String stateStr;

  switch (currentState) {
  case BLEPeripheralState::PAIRING:
    stateStr = DEVICE_NAME;
    break;
  case BLEPeripheralState::PAIRED:
    stateStr = "Paired.";
    break;
  default:
    break;
  }

  auto context = TFTDrawingContext::getScreenDrawingContext();
  int32_t screenWidth = context->size().width;
  Screen.clear();
  context->drawXBitmap(bluetooth_logo_bits,
                       Rect((screenWidth - bluetooth_logo_width) / 2, 40, bluetooth_logo_width,
                            bluetooth_logo_height),
                       color565(0, 130, 252));
  context->setTextColor(TFT_WHITE);
  context->setFont(4);
  context->setFontSize(1);
  context->setTextAlign(CC_DATUM);
  context->drawString(stateStr, Point(screenWidth / 2, 40 + bluetooth_logo_height + 40));
}
