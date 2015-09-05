#include <stdio.h>
#include <dev/board.h>
#include <arpa/inet.h>

#include "eth.h"


#define MY_MAC  { 0x00, 0x06, 0x98, 0x00, 0x00, 0x01 }
#define MY_IP_ADDR    "192.168.100.3"
#define MY_IP_MASK    "255.255.255.0"
#define MY_IP_GATEWAY "192.168.100.1"

uint8_t eth_init(void)
{
  uint8_t mac[6] = MY_MAC;
  uint32_t ip_addr = inet_addr(MY_IP_ADDR);
  uint32_t ip_mask = inet_addr(MY_IP_MASK);
  uint32_t ip_gateway = inet_addr(MY_IP_GATEWAY);

  NutRegisterDevice(&DEV_ETHER, 0, 0);
  if(NutNetIfConfig2(DEV_ETHER_NAME, mac, ip_addr, ip_mask, ip_gateway))
  {
    printf("ERROR : NutNetIfConfig2\n");
  }

  return 0;
}
