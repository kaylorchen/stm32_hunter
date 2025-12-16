//
// Created by kaylor on 6/21/25.
//

#include "interface.h"

#include "cmsis_os2.h"

Interface &Interface::get_instance() {
  static __attribute__((section(".ccmram"))) Interface interface;
  return interface;
}

void Interface::delay_ms(uint32_t ms) {
  // FreeRTOS delay in milliseconds
  osDelay(ms);
}

