#ifndef _LOST_CONFIG_H_
#define _LOST_CONFIG_H_

#ifdef LOST_CONFIG_mms
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0683585066"
#define LOST_GSM2 "0689350159"
#define LOST_STATUS "LOST/safety/status.php?tab=mms"
#define LOST_EMAIL "LOST/safety/email.php?tab=mms&msg="
#define LOST_INSERT "LOST/charts/insert.php?tab=mms"
#define LOST_PASSWORD "mms"
#endif
#ifdef LOST_CONFIG_bt
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0676970721"
#define LOST_STATUS "LOST/safety/status.php?tab=bt"
#define LOST_EMAIL "LOST/safety/email.php?tab=bt&msg="
#define LOST_INSERT "LOST/charts/insert.php?tab=bt"
#define LOST_PASSWORD "bourdilot"
#endif
#ifdef LOST_CONFIG_lb
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0689350159"
#define LOST_STATUS "LOST/safety/status.php?tab=lb"
#define LOST_EMAIL "LOST/safety/email.php?tab=lb&msg="
#define LOST_INSERT "LOST/charts/insert.php?tab=lb"
#define LOST_PASSWORD "lebomb"
#endif
#ifdef LOST_CONFIG_fr
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0689350159"
#define LOST_STATUS "LOST/safety/status.php?tab=fr"
#define LOST_EMAIL "LOST/safety/email.php?tab=fr&msg="
#define LOST_INSERT "LOST/charts/insert.php?tab=fr"
#define LOST_PASSWORD "frenes"
#endif

#endif
