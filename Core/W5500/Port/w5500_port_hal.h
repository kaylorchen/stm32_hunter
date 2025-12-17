#ifndef _W5500_PORT_HAL_
#define _W5500_PORT_HAL_

#include "Ethernet/wizchip_conf.h"
#include "main.h"
#include "string.h"
#include "stdio.h"

#define W5500_SPI_HANDLE hspi2
#define W5500_RECEIVE(data, len, timeout)                                      \
  HAL_SPI_Receive(&W5500_SPI_HANDLE, data, len, timeout)
#define W5500_TRANSMIT(data, len, timeout)                                     \
  HAL_SPI_Transmit(&W5500_SPI_HANDLE, data, len, timeout)
#define W5500_CS_HIGH()                                                        \
  HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_SET)
#define W5500_CS_LOW()                                                         \
  HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_RESET)
#define W5500_SET()                                                            \
  HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET)
#define W5500_RESET()                                                          \
  HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_RESET)

#define W5500_DELAY_MS(ms) HAL_Delay(ms)



#define DEFAULT_MAC_ADDR    {0x00,0xf1,0xbe,0xc4,0xa1,0x05}
#define DEFAULT_IP_ADDR     {192,168,11,136}
#define DEFAULT_SUB_MASK    {255,255,255,0}
#define DEFAULT_GW_ADDR     {192,168,11,1}
#define DEFAULT_DNS_ADDR    {114,114,114,114}

//#define USE_AUTONEGO

//#define USE_DHCP

extern SPI_HandleTypeDef W5500_SPI_HANDLE;

void w5500_network_info_show(void);
int w5500_init(void);

#endif
