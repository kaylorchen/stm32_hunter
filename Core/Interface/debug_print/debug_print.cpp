//
// Created by kaylor on 7/5/25.
//
#include "debug_print.h"

#include "stdarg.h"
#include "stdio.h"
#include "usart.h"

void DebugPrint::print(char *fmt, ...) {
  char sprint_buf[256];
  va_list args;
  int n;
  va_start(args, fmt);
  n = vsprintf(sprint_buf, fmt, args);
  va_end(args);
  HAL_UART_Transmit(&huart1, (uint8_t *)sprint_buf, n, n);
}
