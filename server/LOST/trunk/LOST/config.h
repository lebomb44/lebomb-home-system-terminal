#ifndef _LOST_CONFIG_H_
#define _LOST_CONFIG_H_

#ifdef LOST_CONFIG_mms
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0683585066"
#define LOST_GSM2 "0689350159"
#define LOST_EMAIL "safety/email_mms.php?msg="
#define LOST_INSERT "LOST/charts/insert_mms.php"
#endif
#ifdef LOST_CONFIG_bt
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0689350159"
#define LOST_EMAIL "safety/email_bt.php?msg="
#define LOST_INSERT "LOST/charts/insert_bt.php"
#endif
#ifdef LOST_CONFIG_lb
#define LOST_GSM_SMS_CENTER_SFR
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0689350159"
#define LOST_EMAIL "safety/email_lb.php?msg="
#define LOST_INSERT "LOST/charts/insert_lb.php"
#endif

#endif
