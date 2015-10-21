#include "../global.h"
#include "../devices/adc.h"
#include "safety.h"
#include "node.h"

#define SAFETY_TEMP_DDR  DDRC
#define SAFETY_TEMP_PORT PORTC
#define SAFETY_TEMP_PIN  PINC
#define SAFETY_TEMP_BIT  0

/*
These pin is already used as an input button
#define SAFETY_HUM_DDR  DDRC
#define SAFETY_HUM_PORT PORTC
#define SAFETY_HUM_PIN  PINC
#define SAFETY_HUM_BIT  1
*/

#define SAFETY_SMOKE_DDR  DDRD
#define SAFETY_SMOKE_PORT PORTD
#define SAFETY_SMOKE_PIN  PIND
#define SAFETY_SMOKE_BIT  2

void safety_init(void)
{
  cbi(SAFETY_TEMP_PORT , SAFETY_TEMP_BIT );
  cbi(SAFETY_TEMP_DDR  , SAFETY_TEMP_BIT );
/*
  These pin is already used as an input button
  sbi(SAFETY_HUM_PORT  , SAFETY_HUM_BIT  );
  cbi(SAFETY_HUM_DDR   , SAFETY_HUM_BIT  );
*/
  cbi(SAFETY_SMOKE_PORT, SAFETY_SMOKE_BIT);
  cbi(SAFETY_SMOKE_DDR , SAFETY_SMOKE_BIT);
}

void safety_cycle(void)
{
  node[NODE_REG_TEMP_VALUE] = adc_get(SAFETY_TEMP_BIT);
/*if(bit_is_set(SAFETY_HUM_PIN  , SAFETY_HUM_BIT  )) { node[NODE_REG_HUM_STATUS  ] = 0; } else { node[NODE_REG_HUM_STATUS  ] = 1; }*/
  if(bit_is_set(SAFETY_SMOKE_PIN, SAFETY_SMOKE_BIT)) { node[NODE_REG_SMOKE_STATUS] = 1; } else { node[NODE_REG_SMOKE_STATUS] = 0; }

  if(node[NODE_REG_TEMP_MAX_CONTROL]) { if(!node[NODE_REG_TEMP_MAX_TRIG]) { if(node[NODE_REG_TEMP_VALUE  ]  > node[NODE_REG_TEMP_MAX_TH]) { node[NODE_REG_TEMP_MAX_TRIG] = 1; } } } else { node[NODE_REG_TEMP_MAX_TRIG] = 0; }
  if(node[NODE_REG_TEMP_MIN_CONTROL]) { if(!node[NODE_REG_TEMP_MIN_TRIG]) { if(node[NODE_REG_TEMP_VALUE  ]  < node[NODE_REG_TEMP_MIN_TH]) { node[NODE_REG_TEMP_MIN_TRIG] = 1; } } } else { node[NODE_REG_TEMP_MIN_TRIG] = 0; }
/*if(node[NODE_REG_HUM_CONTROL     ]) { if(!node[NODE_REG_HUM_TRIG     ]) { if(node[NODE_REG_HUM_STATUS  ]                              ) { node[NODE_REG_HUM_TRIG     ] = 1; } } } else { node[NODE_REG_HUM_TRIG     ] = 0; }*/
  if(node[NODE_REG_SMOKE_CONTROL   ]) { if(!node[NODE_REG_SMOKE_TRIG   ]) { if(node[NODE_REG_SMOKE_STATUS]                              ) { node[NODE_REG_SMOKE_TRIG   ] = 1; } } } else { node[NODE_REG_SMOKE_TRIG   ] = 0; }
}
