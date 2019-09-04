#pragma once

#include <Arduino.h>

#include "../ble/ble_address_t.h"

class Settings {
public:
  // Initializes `AirChargerSettings`.
  void begin();

  bool hasClientAddress();
  ble_address_t clientAddress();
  void clientAddress(ble_address_t value);

  void save();

private:
  bool _hasClientAddress = false;
  uint8_t _clientAddress[6];

  void _touch();
};

extern Settings AirChargerSettings;
