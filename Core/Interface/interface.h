//
// Created by kaylor on 6/21/25.
//

#pragma once
#include "debug_print/debug_print.h"

class Interface: public DebugPrint{
 public:
  static Interface &get_instance() {
    static __attribute__((section(".ccmram"))) Interface interface;
    return interface;
  }
  Interface(const Interface &) = delete;
  Interface &operator=(const Interface &) = delete;
  virtual void print(char *fmt, ...) override;
 private:
  Interface(){}
  ~Interface(){}
};
