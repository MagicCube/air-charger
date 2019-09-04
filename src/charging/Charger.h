#pragma once

#include <Arduino.h>

enum class ChargingState {
  NOT_CHARGING,
  CHARGING
};

class ChargerClass {
public:
  void begin();
  void update();
  bool isCharging();
  ChargingState state();

private:
  ChargerClass();
  ChargingState _state = ChargingState::CHARGING;
  // ChargingState _state = ChargingState::NOT_CHARGING;
};

extern ChargerClass Charger;
