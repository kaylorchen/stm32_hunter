//
// Created by kaylor on 6/21/25.
//

#pragma once
#include "microros.h"

class UserTaskImpl {
public:
  static UserTaskImpl &get_instance();
  UserTaskImpl(const UserTaskImpl &) = delete;
  UserTaskImpl &operator=(const UserTaskImpl &) = delete;
  void UserMainLoopCallback();
  void MicorosTimerCallbackImpl();
  void PrintTaskInfo();

private:
  UserTaskImpl() {}
  ~UserTaskImpl() {}
  Microros microros_;
  const uint16_t timer_loop_period_ms_ = 1000;
};
