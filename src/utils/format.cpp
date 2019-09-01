#include "format.h"

String formatBLEAddress(ble_address_t bytes) {
  char result[20];
  sprintf(result, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", bytes[0], bytes[1], bytes[2], bytes[3], bytes[4],
          bytes[5]);
  return String(result);
}

String formatTime(DateTime dateTime) {
  char result[10];
  sprintf(result, "%02d:%02d:%02d", dateTime.getHours(), dateTime.getMinutes(),
          dateTime.getSeconds());
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
