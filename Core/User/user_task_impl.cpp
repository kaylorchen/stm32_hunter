//
// Created by kaylor on 6/21/25.
//

#include "user_task_impl.h"
#include "main.h"
#include "interface.h"

void UserTaskImpl::UserMainLoopCallback() {
  while (1){
   Interface::get_instance().print("This is a test\r\n");
    HAL_Delay(1000);
  }
}
