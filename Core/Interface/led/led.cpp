//
// Created by kaylor on 7/5/25.
//

#include "led.h"

#include "main.h"

Led::Led() {}

void Led::LedOn(uint8_t index) {
  switch (index) {
    case 0:
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PinState::GPIO_PIN_RESET);
      break;
    case 1:
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PinState::GPIO_PIN_RESET);
      break;
    case 2:
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PinState::GPIO_PIN_RESET);
      break;
    default:
      break;
  }
}

void Led::LedOff(uint8_t index) {
  switch (index) {
    case 0:
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PinState::GPIO_PIN_SET);
      break;
    case 1:
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PinState::GPIO_PIN_SET);
      break;
    case 2:
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PinState::GPIO_PIN_SET);
      break;
    default:
      break;
  }
}

void Led::LedToggle(uint8_t index) {
  switch (index) {
    case 0:
      HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_3);
      break;
    case 1:
      HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4);
      break;
    case 2:
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_9);
      break;
    default:
      break;
  }
}
