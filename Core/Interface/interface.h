//
// Created by kaylor on 6/21/25.
//

#pragma once
#include "debug_print/debug_print.h"
#include "led/led.h"

class Interface : public DebugPrint, public Led {
 public:
   static Interface &get_instance();
   Interface(const Interface &) = delete;
   Interface &operator=(const Interface &) = delete;

 private:
  Interface(){}
  ~Interface(){}
};
