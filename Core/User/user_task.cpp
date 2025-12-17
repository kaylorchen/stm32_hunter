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
void MicrorosTimerCallback() {
  UserTaskImpl::get_instance().MicorosTimerCallbackImpl();
}
#ifdef __cplusplus
}
#endif