#include "MainScene.h"

#include "log.h"

#include "../ble/BLEPeripheral.h"
#include "../charging/Charger.h"
#include "../drawing/tft/TFTDrawingContext.h"
#include "../utils/format.h"

#include "../resources/charging_indicator.h"

MainScene::MainScene() : Scene() {
  _animation.setBlackHoles(_clockView.frame(), _batteryView.frame());
  _chargingIndicatorFrame =
      Rect(_batteryView.frame().left() - charging_indicator_width - 8,
           _batteryView.frame().top() + 8, charging_indicator_width, charging_indicator_height);
}

void MainScene::update() {
  auto now = DateTime::now();
  DateTime time(now);
  if (now > 1000 * 60 * 60) {
    _clockView.timeString(formatTime(time, false));
  }
  _batteryView.batteryLevel(BLEPeripheral.remoteDevice()->batteryLevel());
  _batteryView.isCharging(Charger.isCharging());

  // Always force to redraw.
  // Don't worry, it won't.
  setNeedsRedraw();
}

void MainScene::draw() {
  _animation.redraw();

  _clockView.redraw(true);   // Always force to redraw
  _batteryView.redraw(true); // Always force to redraw

  _drawChargingIndicator();

  Screen.drawConstructionLines();
}

void MainScene::_drawChargingIndicator() {
  auto context = TFTDrawingContext::getScreenDrawingContext();
  if (Charger.isCharging()) {
    context->drawXBitmap(charging_indicator_bits,
                         Rect(_chargingIndicatorFrame.left(), _chargingIndicatorFrame.top(),
                              _chargingIndicatorFrame.width(), _chargingIndicatorFrame.height()),
                         TFT_WHITE);
  } else {
    context->fillRect(Rect(_chargingIndicatorFrame.left(), _chargingIndicatorFrame.top(),
                           _chargingIndicatorFrame.width(), _chargingIndicatorFrame.height()),
                      TFT_BLACK);
  }
}
