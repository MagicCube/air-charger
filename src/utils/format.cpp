#include "format.h"

String formatPercentage(int percentage) {
  char result[5];
  sprintf(result, "%d%%", percentage);
  return String(result);
}

String formatTime(DateTime dateTime, bool includingSeconds) {
  char result[10];
  auto *format = includingSeconds ? "%02d:%02d:%02d" : "%02d : %02d";
  sprintf(result, format, dateTime.getHours(), dateTime.getMinutes(), dateTime.getSeconds());
  return String(result);
}

String formatDate(DateTime dateTime) {
  char result[12];
  sprintf(result, "%d-%02d-%02d", dateTime.getFullYear(), dateTime.getMonth() + 1,
          dateTime.getDate());
  return String(result);
}

String formatDateTime(DateTime dateTime) {
  char result[24];
  sprintf(result, "%d-%02d-%02d %02d:%02d:%02d", dateTime.getFullYear(), dateTime.getMonth() + 1,
          dateTime.getDate(), dateTime.getHours(), dateTime.getMinutes(), dateTime.getSeconds());
  return String(result);
}

String formatBLEAddress(ble_address_t bytes) {
  char result[20];
  sprintf(result, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", bytes[0], bytes[1], bytes[2], bytes[3], bytes[4],
          bytes[5]);
  return String(result);
}
