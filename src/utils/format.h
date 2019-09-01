#pragma once

#include <Arduino.h>

#include "../timing/DateTime.h"
#include "../ble/ble_address_t.h"


String formatDate(DateTime dateTime);
String formatTime(DateTime dateTime, bool includingSeconds = true);
String formatDateTime(DateTime dateTime);

String formatPercentage(int percentage);

String formatBLEAddress(ble_address_t bytes);
