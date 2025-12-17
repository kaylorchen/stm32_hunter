//
// Created by kaylor on 12/17/25.
//
#include "FreeRTOS.h"
#include "task.h"
#include "microros.h"
#include "elog.h"
#include "interface.h"

#include <functional>
extern "C" {
#include "micro_ros.h"
#include "rcl/error_handling.h"
#include "rcl/rcl.h"
#include "rclc/executor.h"
#include "rclc/rclc.h"
#include "rmw_microros/rmw_microros.h"
#include "rmw_microxrcedds_c/config.h"
#include "uxr/client/transport.h"
}
#define MICROROS_TAG "MicroROS"
#define RCCHECK(fn)                                                            \
  {                                                                            \
    rcl_ret_t temp_rc = fn;                                                    \
    if ((temp_rc != RCL_RET_OK)) {                                             \
      elog_e(MICROROS_TAG, "Failed status on %s %d, ret = %d. Aborting.\n",    \
             __FILE__, __LINE__, (int)temp_rc);                                \
      vTaskDelete(NULL);                                                       \
    }                                                                          \
  }
#define RCSOFTCHECK(fn)                                                        \
  {                                                                            \
    rcl_ret_t temp_rc = fn;                                                    \
    if ((temp_rc != RCL_RET_OK)) {                                             \
      elog_e(MICROROS_TAG, "Failed status on %s:%d, ret = %d. Continuing.\n",  \
             __FILE__, __LINE__, (int)temp_rc);                                \
    }                                                                          \
  }

Microros::Microros() {}
Microros::~Microros() {
  // Free resources
  RCCHECK(rcl_publisher_fini(&key_state_publisher_, &node_));
  RCCHECK(rcl_node_fini(&node_));
}

void Microros::CreatePublisher() {
  // create publisher
  RCCHECK(rclc_publisher_init_best_effort(
      &key_state_publisher_, &node_,
      ROSIDL_GET_MSG_TYPE_SUPPORT(kaylordut_interfaces, msg, Key),
      key_state_topic_name_));
}

void Microros::CreateSubscription() {
  // create subscription
  RCCHECK(rclc_subscription_init_best_effort(
      &led_subscription_, &node_,
      ROSIDL_GET_MSG_TYPE_SUPPORT(kaylordut_interfaces, msg, Led),
      led_topic_name_));
  RCCHECK(rclc_executor_add_subscription(
      &executor_, &led_subscription_, &led_command_msg_,
      [](const void *msg) { Microros::LedCallback(msg); }, ON_NEW_DATA));
}

void Microros::LedCallback(const void *msg) {
  const kaylordut_interfaces__msg__Led *led_msg =
      (const kaylordut_interfaces__msg__Led *)msg;
  elog_info("LedCallback", "led_msg->id = %d, led_msg->state = %d", led_msg->id,
            led_msg->value);
  Interface::get_instance().LedSet(led_msg->id, led_msg->value);
}

void Microros::Initialize(void) {
  auto write_func_ptr =
      reinterpret_cast<write_custom_func>(cubemx_transport_write);

  rmw_uros_set_custom_transport(
      false, // Framing disable here. Udp should Use Packet-oriented mode.
      const_cast<char *>(target_ip_addr_and_port), // your Agent's ip address
      cubemx_transport_open, cubemx_transport_close, write_func_ptr,
      cubemx_transport_read);

  rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
  freeRTOS_allocator.allocate = microros_allocate;
  freeRTOS_allocator.deallocate = microros_deallocate;
  freeRTOS_allocator.reallocate = microros_reallocate;
  freeRTOS_allocator.zero_allocate = microros_zero_allocate;

  if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
    elog_error("MicroROS", "Error on default allocators (line %d)\r\n",
               __LINE__);
  } else {
    elog_info("MicroROS", "set default allocator successfully\r\n");
  }
  // micro-ROS app
  allocator_ = rcl_get_default_allocator();
  auto init_options = rcl_get_zero_initialized_init_options();
  RCCHECK(rcl_init_options_init(&init_options, allocator_));
  RCCHECK(rcl_init_options_set_domain_id(&init_options, domain_id_));
  // create init_options
  RCCHECK(rclc_support_init_with_options(&support_, 0, NULL, &init_options,
                                         &allocator_));
  // create node
  RCCHECK(rclc_node_init_default(&node_, node_name_, namespace_, &support_));
  // create executor
  RCCHECK(rclc_executor_init(&executor_, &support_.context, 2, &allocator_));
  // create application after creating executor and node
  CreatePublisher();
  CreateSubscription();
  for (int i = 0;
       (i < executor_.max_handles && executor_.handles[i].initialized); ++i) {
    elog_info("Executor", "handles[%d].type=%d, max = %d", i,
              executor_.handles[i].type, executor_.max_handles);
  }
}

void Microros::Run(void) {
  elog_info("MicroROS", "Micro-ROS app started. Waiting for agent to be ready.");
  Interface::get_instance().MicrorosTimerStart();
  elog_info("MicroROS", "Microros Timer started.");
  while (true) {
    auto status = rclc_executor_spin_some(&executor_, 1000000);
    switch (status) {
    case RCL_RET_INVALID_ARGUMENT:
      elog_error("MicroROS", "executor RCL_RET_INVALID_ARGUMENT");
      break;
    case RCL_RET_TIMEOUT:
      elog_warn("MicroROS", "executor RCL_RET_TIMEOUT");
      break;
    case RCL_RET_ERROR:
      elog_error("MicroROS", "executor RCL_RET_ERROR");
      break;
    default:
      break;
    }
    vTaskDelay(1);
  }
}

void Microros::PublishKeyState() {
  kaylordut_interfaces__msg__Key key_state_msg = {0};
  key_state_msg.value = Interface::get_instance().GetKeyState(0);
  RCCHECK(rcl_publish(&key_state_publisher_, &key_state_msg, nullptr));
}

