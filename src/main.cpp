#include <Arduino.h>

// You can define your own settings in conf.h
#include "conf.h"

#include <soc/rtc_cntl_reg.h>
#include <soc/soc.h>

#include "AirCharger.h"

void setup() {
  // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  AirCharger.begin(DEVICE_NAME);
}

void loop() {
}
