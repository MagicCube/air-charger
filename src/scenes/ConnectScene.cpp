#include "ConnectScene.h"

#include "../resources/bluetooth_logo.h"

bool ConnectScene::update(bool forceRedraw) {
  BLEPeripheralState currentState = BLEPeripheral.state();
  bool redraw = false;
  if (forceRedraw) {
    redraw = true;
  } else if (_lastState != currentState) {
    redraw = true;
  }
  _lastState = BLEPeripheral.state();
  return redraw;
}

void ConnectScene::redraw(TFT_eSPI *canvas) {
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

  canvas->fillScreen(TFT_BLACK);
  canvas->drawXBitmap((TFT_WIDTH - bluetooth_logo_width) / 2, 40, bluetooth_logo_bits,
                      bluetooth_logo_width, bluetooth_logo_height, TFT_BLUE);
  canvas->setTextColor(TFT_WHITE);
  canvas->setTextFont(4);
  canvas->setTextSize(1);
  canvas->setTextDatum(CC_DATUM);
  canvas->drawString(stateStr, TFT_WIDTH / 2, 40 + bluetooth_logo_height + 40);
}
