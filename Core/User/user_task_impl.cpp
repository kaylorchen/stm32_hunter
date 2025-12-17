//
// Created by kaylor on 6/21/25.
//

#include "user_task_impl.h"
#include "FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#include "Port/w5500_port_hal.h"
}
#endif
#include "elog.h"
#include "interface.h"
#include "main.h"
#include "portable.h"
#include "stdio.h"
#include "task.h"

UserTaskImpl &UserTaskImpl::get_instance() {
  static __attribute__((section(".ccmram"))) UserTaskImpl instance;
  return instance;
}

void UserTaskImpl::PrintTaskInfo() {
  char buffer[512] = {0};
  auto n = snprintf(buffer, sizeof(buffer),
                    "\r\nfree heap size: %d bytes\r\nname          state"
                    " prior free(words) order\r\n",
                    xPortGetFreeHeapSize());
  vTaskList(buffer + n);
  const char *TAG = "MicroROS";
  elog_i(TAG, buffer);
}

void UserTaskImpl::UserMainLoopCallback() {
  auto &interface = Interface::get_instance();
  // 使用串口作为日志输出，所以可以在网络之前初始化，
  // 如果使用网络，则需要放在网络初始化之后再初始化log
  elog_init();
  elog_start();
  if (w5500_init() != 0) {
    elog_e("UserMainLoop", "w5500_init failed");
    interface.SystemReset();
  }
  elog_info("UserMainLoop", "w5500_init done");
  microros_.Initialize();
  elog_info("UserMainLoop", "microros_init done");
  microros_.Run();
  while (1){
    elog_a("UserMainLoop", "assert");
    elog_e("UserMainLoop", "error");
    elog_w("UserMainLoop", "warn");
    elog_i("UserMainLoop", "info");
    elog_d("UserMainLoop", "debug");
    elog_v("UserMainLoop", "verbose");
    interface.LedToggle(0);
    interface.LedToggle(1);
    interface.LedToggle(2);
    interface.delay_ms(2000);
  }
}

void UserTaskImpl::MicorosTimerCallbackImpl() {
  auto &interface = Interface::get_instance();
  // elog_i("MicorosTimer", "MicorosTimerCallback");
  static uint16_t _1000ms_counter = 0;
  _1000ms_counter++;
  elog_info("MicorosTimerCallbackImpl", "_1000ms_counter = %d", _1000ms_counter);
  if (_1000ms_counter == timer_loop_period_ms_) {
    _1000ms_counter = 0;
    microros_.PublishKeyState();
  }
}

