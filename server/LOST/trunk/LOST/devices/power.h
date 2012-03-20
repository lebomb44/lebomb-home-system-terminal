#ifndef _POWER_H_
#define _POWER_H_

__BEGIN_DECLS

typedef enum _POWER_T
{
  POWER_0 = 0,
  POWER_1,
  POWER_2,
  POWER_3,
  POWER_MAX
} POWER_T;

extern uint8_t power_init(void);
extern void power_set(POWER_T power, uint8_t status);

__END_DECLS

#endif
