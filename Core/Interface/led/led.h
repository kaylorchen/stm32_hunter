//
// Created by kaylor on 7/5/25.
//

#pragma once
#include "stdint.h"

class Led {
 public:
  Led();
  void LedOn(uint8_t index);
  void LedOff(uint8_t index);
  void LedToggle(uint8_t index);
};
