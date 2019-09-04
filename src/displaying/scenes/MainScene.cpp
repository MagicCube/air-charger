#include "MainScene.h"

#include "log.h"

#include "../../ble/BLEPeripheral.h"
#include "../../charging/Charger.h"
#include "../../utils/format.h"

#include "../../resources/charging_indicator.h"

#define TFT_GREY 0x4208

#define BATTERY_HEAD_WIDTH 6
#define BATTERY_ROUNDNESS 4
#define BATTERY_PADDING 5

MainScene::MainScene()
    : _clockFrame((TFT_WIDTH - 160) / 2, 40, 160, 52),
      _batteryFrame((240 - 150) / 2 + BATTERY_HEAD_WIDTH / 2 + 2, 128, 160, 60),
      _chargingIndicatorFrame(_batteryFrame.left() - charging_indicator_width - 8,
                              _batteryFrame.top() + 8, charging_indicator_width,
                              charging_indicator_height) {
}

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
  _drawBackground(canvas);
  _drawClock(canvas);
  _drawBattery(canvas);
  _drawChargingIndicator(canvas);
  _lastRedraw = millis();
}

void MainScene::_drawBackground(TFT_eSPI *canvas) {
  if (_animation == nullptr) {
    _animation = new StarfieldAnimation(canvas);
    _animation->begin();
  }
  _animation->redraw();
}

void MainScene::_drawClock(TFT_eSPI *canvas) {
  auto now = DateTime::now();
  DateTime time(now);
  if (now < 1000 * 60 * 60) {
    return;
  }
  String timeString = formatTime(time, false);
  if (_clock == nullptr) {
    _clock = new TFT_eSprite(canvas);
    _clock->setColorDepth(1);
  }
  _clock->createSprite(_clockFrame.width(), _clockFrame.height());
  _clock->setTextColor(TFT_WHITE);
  _clock->setTextFont(7);
  _clock->setTextSize(1);
  _clock->setTextDatum(CC_DATUM);
  _clock->drawString(timeString, _clock->width() / 2, _clock->height() / 2);
  _clock->pushSprite(_clockFrame.left(), _clockFrame.top());
  _clock->deleteSprite();
}

void MainScene::_drawBattery(TFT_eSPI *canvas) {
  if (_battery == nullptr) {
    _battery = new TFT_eSprite(canvas);
    _battery->setColorDepth(8);
  }
  _battery->createSprite(_batteryFrame.width(), _batteryFrame.height());

  _battery->drawRoundRect(0, 0, _batteryFrame.width() - BATTERY_HEAD_WIDTH - 3,
                          _batteryFrame.height(), BATTERY_HEAD_WIDTH, TFT_WHITE);

  int headHeight = _batteryFrame.height() / 2;
  _battery->fillRoundRect(_batteryFrame.width() - BATTERY_HEAD_WIDTH,
                          (_batteryFrame.height() - headHeight) / 2, BATTERY_HEAD_WIDTH, headHeight,
                          BATTERY_ROUNDNESS, TFT_WHITE);

  float batteryLevel = BLEPeripheral.remoteDevice()->batteryLevel();
  int batteryWidth =
      ((float)(_batteryFrame.width() - BATTERY_HEAD_WIDTH - BATTERY_PADDING * 2 - 3)) *
      (batteryLevel / 100);
  auto batteryColor = Charger.isCharging() ? TFT_DARKGREEN : TFT_GREY;
  if (batteryLevel <= 10) {
    batteryColor = TFT_RED;
  } else if (batteryLevel <= 20) {
    batteryColor = TFT_ORANGE;
  }
  auto batteryTextColor = TFT_WHITE;
  _battery->fillRect(BATTERY_PADDING, BATTERY_PADDING, batteryWidth,
                     _batteryFrame.height() - BATTERY_PADDING * 2, batteryColor);

  _battery->setTextColor(batteryTextColor);
  _battery->setFreeFont(&FreeSansBold18pt7b);
  _battery->setTextSize(1);
  _battery->setTextDatum(CC_DATUM);
  _battery->drawString(formatPercentage(batteryLevel),
                       (_batteryFrame.width() - BATTERY_HEAD_WIDTH - 3) / 2,
                       _batteryFrame.height() / 2);

  _battery->pushSprite(_batteryFrame.left(), _batteryFrame.top());
  _battery->deleteSprite();
}

void MainScene::_drawChargingIndicator(TFT_eSPI *canvas) {
  if (Charger.isCharging()) {
    canvas->drawXBitmap(_chargingIndicatorFrame.left(), _chargingIndicatorFrame.top(),
                        charging_indicator_bits, _chargingIndicatorFrame.width(),
                        _chargingIndicatorFrame.height(), TFT_WHITE);
  } else {
    canvas->fillRect(_chargingIndicatorFrame.left(), _chargingIndicatorFrame.top(),
                     _chargingIndicatorFrame.width(), _chargingIndicatorFrame.height(), TFT_BLACK);
  }
}
