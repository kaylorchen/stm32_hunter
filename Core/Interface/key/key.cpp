//
// Created by kaylor on 12/17/25.
//

#include "key.h"
#include "gpio.h"

Key::Key() {}
Key::~Key() {}
int8_t Key::GetKeyState(uint8_t id) {
  switch (id) {
  case 0:
    return HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin);
  case 1:
    return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
  case 2:
    return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
  case 3:
    return HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin);
  default:
    return -1;
  }
}


