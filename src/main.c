# include <stdint.h>
#include "HAL/relay.h"


int main()
{
  relay_init();
  while (1)
  {
    relay_control(RELAY_1, RELAY_ON);
    relay_control(RELAY_2, RELAY_ON);
    SysCtlDelay(10000000);
    relay_control(RELAY_1, RELAY_OFF);
    relay_control(RELAY_2, RELAY_OFF);
    SysCtlDelay(10000000);
  }
  
  return 0;
}
