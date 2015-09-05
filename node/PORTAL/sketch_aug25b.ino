#include <Fifo_U16.h>
#include <HomeEasy.h>

#define LED_pin 13
#define RELAY_LEFT_pin 7
#define RELAY_RIGHT_pin 8
#define IR_POWER_pin 10
#define IR_STATUS_pin 3
#define RF_IN_pin 2
#define MOTOR_SENSE_pin A0
#define MOTOR_PWM_pin 6

#define PORTAL_COMPLETE_POSITION (PORTAL_START_SLOT+PORTAL_CRUISE_SLOT+PORTAL_STOP_SLOT+PORTAL_FINISH_SLOT)
#define PORTAL_START_SLOT 3000
#define PORTAL_CRUISE_SLOT 6000
#define PORTAL_STOP_SLOT 3000
#define PORTAL_FINISH_SLOT 8000

#define PORTAL_CMD_NONE (-1)
#define PORTAL_CMD_CLOSE 0
#define PORTAL_CMD_OPEN  1

#define PORTAL_MAX_FORCE PORTAL_START_SLOT
#define MOTOR_MAX_CURRENT 70
#define PORTAL_SLOW_FORCE (PORTAL_MAX_FORCE/5)
#define MOTOR_MAX_SLOW_CURRENT 15

HomeEasy homeEasy;
int portal_cmd = PORTAL_CMD_NONE;
uint16_t portal_position = 0;
uint16_t portal_force = 0;
int motor_max_current = 0;


void setup()
{
  homeEasy.init();
  // initialize serial communications and wait for port to open:
  Serial.begin(115200);
  pinMode(13, OUTPUT); 
  pinMode(RELAY_LEFT_pin, OUTPUT);
  digitalWrite(RELAY_LEFT_pin, LOW);
  pinMode(RELAY_RIGHT_pin, OUTPUT);
  digitalWrite(RELAY_RIGHT_pin, LOW);
  pinMode(IR_POWER_pin, OUTPUT);
  digitalWrite(IR_POWER_pin, LOW);
  pinMode(IR_STATUS_pin, INPUT);
  pinMode(RF_IN_pin, INPUT);
  pinMode(MOTOR_SENSE_pin, INPUT);
  pinMode(MOTOR_PWM_pin, OUTPUT);
  digitalWrite(MOTOR_PWM_pin, LOW);
}

void loop()
{
  homeEasy.run();
  if(true == homeEasy.rxCodeIsReady()) {
    Serial.print(homeEasy.rxGetCode(), HEX);Serial.print(" : ");
    Serial.print(homeEasy.rxGetManufacturer(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetGroup(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetDevice(), HEX);Serial.print("-");
    Serial.print(homeEasy.rxGetStatus(), HEX);Serial.println();
    /* Check the authorized codes */
    if(((0xFCE1CE == homeEasy.rxGetManufacturer()) && (0x0 == homeEasy.rxGetGroup()) && (0x2 == homeEasy.rxGetDevice())) \
    || ((0xFCBDD6 == homeEasy.rxGetManufacturer()) && (0x0 == homeEasy.rxGetGroup()) && (0x2 == homeEasy.rxGetDevice()))) {
      digitalWrite(IR_POWER_pin, HIGH);
      delay(1);
      if(PORTAL_CMD_CLOSE == homeEasy.rxGetStatus()) {
        digitalWrite(RELAY_LEFT_pin, HIGH);
        digitalWrite(RELAY_RIGHT_pin, LOW);
        portal_cmd = PORTAL_CMD_CLOSE;
        portal_position = 0;
        portal_force = 0;
      }
      if(PORTAL_CMD_OPEN == homeEasy.rxGetStatus()) {
        digitalWrite(RELAY_LEFT_pin, LOW);
        digitalWrite(RELAY_RIGHT_pin, HIGH);
        portal_cmd = PORTAL_CMD_OPEN;
        portal_position = 0;
        portal_force = 0;
      }
      delay(1);
    }
    homeEasy.rxRelease();
  }

  /* Check the IR barrier */
  if(LOW == digitalRead(IR_STATUS_pin)) {
    //portal_cmd = PORTAL_CMD_NONE;
    //portal_force = 0;
  }


  if((PORTAL_CMD_CLOSE == portal_cmd) || (PORTAL_CMD_OPEN == portal_cmd)) {
    if(PORTAL_COMPLETE_POSITION > portal_position) {
      delay(1);
      portal_position++;
      if(PORTAL_START_SLOT > portal_position) {
        if(PORTAL_MAX_FORCE > portal_force) {
          portal_force++;
        }
        motor_max_current = MOTOR_MAX_CURRENT;
      }
      if(((PORTAL_START_SLOT) < portal_position) && \
         ((PORTAL_START_SLOT+PORTAL_CRUISE_SLOT) > portal_position)) {
        portal_force = PORTAL_MAX_FORCE;
        motor_max_current = MOTOR_MAX_CURRENT;
      }

      if(((PORTAL_START_SLOT+PORTAL_CRUISE_SLOT) < portal_position) && \
         ((PORTAL_START_SLOT+PORTAL_CRUISE_SLOT+PORTAL_STOP_SLOT) > portal_position)) {
        if(PORTAL_SLOW_FORCE < portal_force) {
          portal_force--;
        }
        motor_max_current = MOTOR_MAX_CURRENT;
      }
      if((PORTAL_START_SLOT+PORTAL_CRUISE_SLOT+PORTAL_STOP_SLOT) < portal_position) {
        portal_force = PORTAL_SLOW_FORCE;
        motor_max_current = MOTOR_MAX_SLOW_CURRENT;
      }
    }
  }

  /* Back to idle mode : everything OFF */
  if((motor_max_current < analogRead(MOTOR_SENSE_pin)) || \
     (0 == portal_position) || (PORTAL_COMPLETE_POSITION == portal_position)) {
    digitalWrite(MOTOR_PWM_pin, LOW);
    digitalWrite(RELAY_LEFT_pin, LOW);
    digitalWrite(RELAY_RIGHT_pin, LOW);
    digitalWrite(IR_POWER_pin, LOW);
    portal_cmd = PORTAL_CMD_NONE;
    portal_position = 0;
    portal_force = 0;
  }
  /* Clone LED status on RF signal */
  //digitalWrite(MOTOR_PWM_pin, HIGH);
  analogWrite(MOTOR_PWM_pin, map(portal_force, 0, PORTAL_MAX_FORCE, 0, 255));
  //Serial.println(portal_force, DEC);
  digitalWrite(LED_pin, digitalRead(RF_IN_pin));
  //Serial.println(analogRead(MOTOR_SENSE_pin), DEC);
}

