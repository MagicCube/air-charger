#include "format.h"

String formatBLEAddress(uint8_t *bytes) {
  char result[20];
  sprintf(result, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", bytes[0], bytes[1], bytes[2], bytes[3], bytes[4],
          bytes[5]);
  return String(result);
}
