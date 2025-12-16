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
  auto &interface = Interface::get_instance();
  elog_init();
  elog_start();
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
