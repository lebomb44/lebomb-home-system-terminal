#ifndef _LOST_CONFIG_H_
#define _LOST_CONFIG_H_

#ifdef LOST_CONFIG_mms
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0683585066"
#define LOST_GSM2 "0689350159"
#define LOST_STATUS "LOST/safety/mms_status.php"
#define LOST_EMAIL "LOST/safety/mms_email.php?msg="
#define LOST_INSERT "LOST/charts/mms_insert.php"
#endif
#ifdef LOST_CONFIG_bt
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0689350159"
#define LOST_STATUS "LOST/safety/bt_status.php"
#define LOST_EMAIL "LOST/safety/bt_email.php?msg="
#define LOST_INSERT "LOST/charts/bt_insert.php"
#endif
#ifdef LOST_CONFIG_lb
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0689350159"
#define LOST_STATUS "LOST/safety/lb_status.php"
#define LOST_EMAIL "LOST/safety/lb_email.php?msg="
#define LOST_INSERT "LOST/charts/lb_insert.php"
#endif
#ifdef LOST_CONFIG_fr
#define LOST_GSM_SMS_CENTER_FREE
#define LOST_GSM1 "0689350159"
#define LOST_GSM2 "0689350159"
#define LOST_STATUS "LOST/safety/fr_status.php"
#define LOST_EMAIL "LOST/safety/fr_email.php?msg="
#define LOST_INSERT "LOST/charts/fr_insert.php"
#endif

#endif
