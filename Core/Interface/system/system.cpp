//
// Created by kaylor on 12/17/25.
//

#include "system.h"
#include "main.h"
System::System() {}
System::~System() {}

void System::SystemReset() {
  SCB->AIRCR = 0x05FA0000 | (uint32_t)0x04; // reset system
}
