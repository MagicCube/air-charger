#pragma once

#include <Arduino.h>

#include "../ble/ble_address_t.h"

enum class RebootReason { UNKNOWN = 1, REPAIR = 10, PAIRED = 11, REMOTE_DEVICE_DISCONNECT = 20 };

class Settings {
public:
  // Initializes `AirChargerSettings`.
  void begin();

  RebootReason rebootReason();
  void rebootReason(RebootReason reason);

  bool hasClientAddress();
  ble_address_t clientAddress();
  void clientAddress(ble_address_t value);

  void save();
  void erase();

private:
  RebootReason _rebootReason = RebootReason::UNKNOWN;
  bool _hasClientAddress = false;
  uint8_t _clientAddress[6];

  void _touch();
};

extern Settings AirChargerSettings;
