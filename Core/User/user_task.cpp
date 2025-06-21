//
// Created by kaylor on 6/21/25.
//

#include "user_task.h"
#include "user_task_impl.h"
#ifdef __cplusplus
extern "C" {
#endif
void UserMainLoop() {
  UserTaskImpl::get_instance().UserMainLoopCallback();
}

#ifdef __cplusplus
}
#endif