#include "MainScene.h"

#include "log.h"

#include "../../ble/BLEPeripheral.h"
#include "../../charging/Charger.h"
#include "../../displaying/Screen.h"
#include "../../utils/format.h"

#include "../../resources/charging_indicator.h"

bool MainScene::update(bool forceRedraw) {
  bool redraw = false;
  if (forceRedraw) {
    redraw = true;
  } else if (millis() - _lastRedraw > UPDATE_INTERVAL) {
    redraw = true;
  }
  return redraw;
}

void MainScene::redraw(TFT_eSPI *canvas) {
  _drawBackground();
  _drawClock();
  _drawBattery();
  _drawChargingIndicator();
  _lastRedraw = millis();
}

void MainScene::_drawBackground() {
  if (_animation == nullptr) {
    _animation = new StarfieldAnimation();
    _animation->begin();
  }
  _animation->redraw();
}

void MainScene::_drawClock() {
  if (_clockView == nullptr) {
    _clockView = new ClockView();
  }
  auto now = DateTime::now();
  DateTime time(now);
  if (now < 1000 * 60 * 60) {
    return;
  }
  _clockView->timeString(formatTime(time, false));
  _clockView->redraw(true); // Always force redraw (cached)
}

void MainScene::_drawBattery() {
  if (_batteryView == nullptr) {
    _batteryView = new BatteryView();
  }
  _batteryView->batteryLevel(BLEPeripheral.remoteDevice()->batteryLevel());
  _batteryView->isCharging(Charger.isCharging());
  _batteryView->redraw(true); // Always force redraw (cached)
}

void MainScene::_drawChargingIndicator() {
  auto context = Screen.drawingContext();
  auto chargingIndicatorFrame =
      Rect(_batteryView->frame().left() - charging_indicator_width - 8,
           _batteryView->frame().top() + 8, charging_indicator_width,
           charging_indicator_height);
  if (Charger.isCharging()) {
    context->drawXBitmap(charging_indicator_bits,
                         Rect(chargingIndicatorFrame.left(), chargingIndicatorFrame.top(),
                              chargingIndicatorFrame.width(), chargingIndicatorFrame.height()),
                         TFT_WHITE);
  } else {
    context->fillRect(Rect(chargingIndicatorFrame.left(), chargingIndicatorFrame.top(),
                           chargingIndicatorFrame.width(), chargingIndicatorFrame.height()),
                      TFT_BLACK);
  }
}
