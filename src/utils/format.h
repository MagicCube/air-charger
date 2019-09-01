#pragma once

#include <Arduino.h>

#include "../ble/ble_address_t.h"
#include "../timing/DateTime.h"

String formatBLEAddress(ble_address_t bytes);
String formatDate(DateTime dateTime);
String formatTime(DateTime dateTime);
String formatDateTime(DateTime dateTime);
