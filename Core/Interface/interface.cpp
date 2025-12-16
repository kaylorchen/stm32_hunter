//
// Created by kaylor on 6/21/25.
//

#include "interface.h"

Interface &Interface::get_instance() {
  static __attribute__((section(".ccmram"))) Interface interface;
  return interface;
}
