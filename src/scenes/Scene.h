#pragma once

#include <Arduino.h>

#include "../displaying/Screen.h"
#include "../views/View.h"

class Scene : public View {
public:
  Scene() : View(Screen.bounds()) {
  }
};
