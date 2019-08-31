#include "Settings.h"

#include <EEPROM.h>

#include "log.h"
#include "../utils/format.h"

void Settings::begin() {
  LOG_I("Loading settings from EEPROM...");
  EEPROM.begin(7);
  LOG_D("Reading previous settings from EEPROM...");
  if (EEPROM.read(0)) {
    _hasClientAddress = true;
    for (int i = 0; i < 6; i++) {
      _clientAddress[i] = EEPROM.read(i + 1);
    }
    LOG_D("Saved client address was found: [%s]", formatBLEAddress(_clientAddress).c_str());
  } else {
    LOG_D("No previous setting wa found in EEPROM.");
    _hasClientAddress = false;
  }
}

bool Settings::hasClientAddress() {
  return _hasClientAddress;
}

ble_address_t Settings::getClientAddress() {
  return _clientAddress;
}

void Settings::setClientAddress(ble_address_t address) {
  LOG_D("[EEPROM] sets client address.");
  _touch();
  for (int i = 0; i < 6; i++) {
    EEPROM.write(i + 1, address[i]);
  }
  _hasClientAddress = true;
}

void Settings::save() {
  EEPROM.commit();
  LOG_D("[EEPROM] has been <SAVED>.");
}

void Settings::_touch() {
  EEPROM.write(0, 1);
}

Settings AirChargerSettings;
