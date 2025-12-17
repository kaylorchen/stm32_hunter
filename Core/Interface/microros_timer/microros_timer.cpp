//
// Created by kaylor on 12/17/25.
//

#include "microros_timer.h"
#include "tim.h"

void MicrorosTimer::MicrorosTimerStart() {
  HAL_TIM_Base_Start_IT(&htim6);
}
void MicrorosTimer::MicrorosTimerStop() {
  HAL_TIM_Base_Stop_IT(&htim6);
}

