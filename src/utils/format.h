#pragma once

#include <Arduino.h>

#include "../ble/ble_address_t.h"

String formatBLEAddress(ble_address_t bytes);
