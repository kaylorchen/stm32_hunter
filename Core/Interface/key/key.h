//
// Created by kaylor on 12/17/25.
//

#pragma once
#include <stdint.h>

class Key {
public:
  Key();
  ~Key();
  int8_t GetKeyState(uint8_t id);
};
