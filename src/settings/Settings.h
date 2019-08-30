#pragma once

#include <Arduino.h>

class Settings {
public:
  // Initializes `AirChargerSettings`.
  void begin();

  bool hasClientAddress();
  uint8_t* getClientAddress();
  void setClientAddress(uint8_t *address);

  void save();

private:
  bool _hasClientAddress = false;
  uint8_t _clientAddress[6];

  void _touch();
};

extern Settings AirChargerSettings;
