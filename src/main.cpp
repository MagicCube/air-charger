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
  Serial.println("\n");
  Serial.println("          _         _____ _");
  Serial.println("    /\\   (_)       / ____| |");
  Serial.println("   /  \\   _ _ __  | |    | |__   __ _ _ __ __ _  ___ _ __ ");
  Serial.println("  / /\\ \\ | | '__| | |    | '_ \\ / _` | '__/ _` |/ _ \\ '__|");
  Serial.println(" / ____ \\| | |    | |____| | | | (_| | | | (_| |  __/ |");
  Serial.println("/_/    \\_\\_|_|     \\_____|_| |_|\\__,_|_|  \\__, |\\___|_|");
  Serial.println("                                          |___/\n");
  AirCharger.begin(DEVICE_NAME);
  Serial.println();
}

void loop() {
}
