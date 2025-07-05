//
// Created by kaylor on 6/21/25.
//

#include "user_task_impl.h"

#include "elog.h"
#include "interface.h"
#include "main.h"

void UserTaskImpl::UserMainLoopCallback() {
  elog_init();
  elog_start();
  while (1){
    elog_a("UserMainLoop", "assert");
    elog_e("UserMainLoop", "error");
    elog_w("UserMainLoop", "warn");
    elog_i("UserMainLoop", "info");
    elog_d("UserMainLoop", "debug");
    elog_v("UserMainLoop", "verbose");
    HAL_Delay(1000);
  }
}
