#include <inttypes.h>

#include <ID.h>
#include <HKTM.h>
#include <Relai.h>
#include <Servo.h>
#include <LB_NRF24.h>

HKTM roverHKTM;
Relai relaiCam;
Servo servoL;
Servo servoR;
Servo servoCamLR;
Servo servoCamUD;
Servo servoCharge;
LB_NRF24 nrf24;

void setup() {
  roverHKTM.init();
  relaiCam.init();
  servoL.init();
  servoR.init();
  servoCamLR.init();
  servoCamUD.init();
  servoCharge.init();
  nrf24.init();

  roverHKTM.register((uint8_t *) roverHKTM.getStateAddr(), sizeof(roverHKTM.getState()));
  roverHKTM.register((uint8_t *) servoL.getAngleAddr(), sizeof(servoL.getAngle()));
  roverHKTM.register((uint8_t *) servoR.getAngleAddr(), sizeof(servoR.getAngle()));
  roverHKTM.register((uint8_t *) relaiCam.getStateAddr(), sizeof(relaiCam.getState()));
  roverHKTM.register((uint8_t *) servoCamLR.getAngleAddr(), sizeof(servoCamLR.getAngle()));
  roverHKTM.register((uint8_t *) servoCamUD.getAngleAddr(), sizeof(servoCamUD.getAngle()));
  roverHKTM.register((uint8_t *) servoCharge.getAngleAddr(), sizeof(servoCharge.getAngle()));
}

void loop() {
  nrf24.run();
  if(true == nrf24.rxIsReady())
  {
    if(ROVER_CMD_HKTM == nrf24.rxGetCmd()) { roverHKTM.setState(nrf24.rxGetData()[0]); }
    if(ROVER_CMD_CAM_POWER == nrf24.rxGetCmd()) { relaiCam.setState(nrf24.rxGetData()[0]); }
    if(ROVER_CMD_CAM_LR == nrf24.rxGetCmd()) { servoCamLR.set(nrf24.rxGetData()[0]); }
    if(ROVER_CMD_CAM_UD == nrf24.rxGetCmd()) { servoCamUD.set(nrf24.rxGetData()[0]); }
    if(ROVER_CMD_CHARGE == nrf24.rxGetCmd()) { servoCharge.set(nrf24.rxGetData()[0]); }
    if(ROVER_CMD_FWD == nrf24.rxGetCmd()) { servoL.set(); servoR.set(); }
    if(ROVER_CMD_TURN == nrf24.rxGetCmd()) { servoL.set(); servoR.set(); }
    if(ROVER_CMD_STOP == nrf24.rxGetCmd()) { servoL.set(180); servoR.set(180); }
    nrf24.rxRelease();
  }
  if(true == roverHKTM.getState())
  {
    if(roverHKTM.getLastTxTime() + 1000 < getCurrentTime())
    {
      if(true == nrf24.txIsReady())
      {
        roverHKTM.refresh();
        nrf24.send(ROVER_ID, LOST_ID, ROVER_HKTM, roverHKTM.getLen(), roverHKTM.getData());
        roverHKTM.setLastTxTime(getCurrentTime());
      }
    }
  }
}
