//
// Created by kaylor on 12/17/25.
//

#pragma once

#ifdef __cplusplus
extern "C" {
#include "rcl/publisher.h"
#include "rclc/rclc.h"
#include "rclc/executor.h"
#include "kaylordut_interfaces/msg/key.h"
}
#endif

class Microros {
public:
  Microros();
  ~Microros();
  void Initialize(void);
  void Run(void);
  void PublishKeyState();

private:
  const char *target_ip_addr_and_port = "192.168.11.2:8888";
  const size_t domain_id_ = 101;
  const char *node_name_ = "microros_node_from_stm32";
  const char *namespace_ = "";
  rclc_support_t support_;
  rcl_time_point_value_t time_point_;
  rcl_allocator_t allocator_;
  rcl_node_t node_;
  rcl_publisher_t key_state_publisher_;
  const char *key_state_topic_name_ = "key_state";
  kaylordut_interfaces__msg__Key key_state_msg_;
  rclc_executor_t executor_;
};
