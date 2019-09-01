#include "Charger.h"

void ChargerClass::begin() {

}

void ChargerClass::update() {

}

ChargingState ChargerClass::state() {
  return _state;
}

bool ChargerClass::isCharging() {
  return _state == ChargingState::CHARGING;
}

ChargerClass Charger;
