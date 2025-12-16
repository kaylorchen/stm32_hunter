//
// Created by kaylor on 6/21/25.
//

#include "user_task_impl.h"

#include "elog.h"
#include "interface.h"
#include "main.h"

UserTaskImpl &UserTaskImpl::get_instance() {
  static __attribute__((section(".ccmram"))) UserTaskImpl instance;
  return instance;
}

void UserTaskImpl::UserMainLoopCallback() {
  auto &instance = Interface::get_instance();
  elog_init();
  elog_start();
  while (1){
    elog_a("UserMainLoop", "assert");
    elog_e("UserMainLoop", "error");
    elog_w("UserMainLoop", "warn");
    elog_i("UserMainLoop", "info");
    elog_d("UserMainLoop", "debug");
    elog_v("UserMainLoop", "verbose");
    instance.LedToggle(0);
    instance.LedToggle(1);
    instance.LedToggle(2);
    HAL_Delay(1000);
  }
}
