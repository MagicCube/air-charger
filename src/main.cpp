#include <Arduino.h>
#include <BLEDevice.h>

#include "conf.h"

void setup() {
  BLEDevice::init(DEVICE_NAME);
}

void loop() {
}
