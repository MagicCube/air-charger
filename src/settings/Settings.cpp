#include "Settings.h"

#include <EEPROM.h>

#include "../utils/format.h"
#include "log.h"

#define PAIRED_FLAG 200

void AirChargerSettingsClass::begin() {
  LOG_I("Loading settings from EEPROM...");
  EEPROM.begin(8);
  LOG_D("Reading previous settings from EEPROM...");

  if (EEPROM.read(0) == PAIRED_FLAG) {
    bool _clientAddressAvailable = false;
    for (uint8_t i = 0; i < 6; i++) {
      _clientAddress[i] = EEPROM.read(i + 2);
      if (_clientAddress[i] != 255 && _clientAddress != 0) {
        _clientAddressAvailable = true;
      }
    }
    if (_clientAddressAvailable) {
      _hasClientAddress = true;
    }
  }
  if (_hasClientAddress) {
    LOG_D("Saved client address was found: [%s]", formatBLEAddress(_clientAddress).c_str());
  } else {
    LOG_D("No previous setting wa found in EEPROM.");
  }

  uint8_t byte = EEPROM.read(1);
  LOG_D("Reboot reason: %d", byte);
  if (byte == 1 || byte == 10 || byte == 11 || byte == 20) {
    _rebootReason = (AirChargerRebootReason)byte;
    EEPROM.write(1, 0);
    EEPROM.commit();
  }
}

AirChargerRebootReason AirChargerSettingsClass::rebootReason() {
  return _rebootReason;
}
void AirChargerSettingsClass::rebootReason(AirChargerRebootReason reason) {
  LOG_D("[EEPROM] sets reboot reason.");
  _rebootReason = reason;
  EEPROM.write(1, (uint8_t)_rebootReason);
}

bool AirChargerSettingsClass::hasClientAddress() {
  return _hasClientAddress;
}

ble_address_t AirChargerSettingsClass::clientAddress() {
  return _clientAddress;
}

void AirChargerSettingsClass::clientAddress(ble_address_t value) {
  LOG_D("[EEPROM] sets client address.");
  _touch();
  for (uint8_t i = 0; i < 6; i++) {
    EEPROM.write(i + 2, value[i]);
  }
  _hasClientAddress = true;
}

void AirChargerSettingsClass::save() {
  EEPROM.commit();
  LOG_D("[EEPROM] has been <SAVED>.");
}

void AirChargerSettingsClass::erase() {
  EEPROM.write(0, 0);
  for (uint8_t i = 0; i < 6; i++) {
    EEPROM.write(i + 2, 0);
  }
}

void AirChargerSettingsClass::_touch() {
  EEPROM.write(0, PAIRED_FLAG);
}

AirChargerSettingsClass AirChargerSettings;
