#ifndef _VOLUME_H_
#define _VOLUME_H_

__BEGIN_DECLS

extern uint8_t volume_init(void);
extern uint8_t volume_status_get(void);
extern uint8_t volume_status_group1_get(void);
extern uint8_t volume_status_group2_get(void);

__END_DECLS

#endif
