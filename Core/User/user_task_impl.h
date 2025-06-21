//
// Created by kaylor on 6/21/25.
//

#pragma once


class UserTaskImpl {
 public:
  static UserTaskImpl &get_instance() {
    static __attribute__((section(".ccmram"))) UserTaskImpl instance;
    return instance;
  }
  UserTaskImpl(const UserTaskImpl &) = delete;
  UserTaskImpl &operator=(const UserTaskImpl &) = delete;
  void UserMainLoopCallback();

 private:
  UserTaskImpl() {}
  ~UserTaskImpl() {}
};
