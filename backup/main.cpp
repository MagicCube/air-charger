#include <Arduino.h>
#include <BLEDevice.h>

#include "Scanner.h"

Scanner scanner;
bool touched = false;

void setup() {
  BLEDevice::init("Battery Indicator");
  scanner.start();
}

void loop() {
  if (!touched && scanner.foundDevice != nullptr) {
    scanner.touch(scanner.foundDevice);
    touched = true;
  }
  delay(1000);
}
