#include <inttypes.h>

#include <ID.h>
#include <Relai.h>
#include <IR.h>
#include <LB_NRF24.h>

Relai relaiCam;
IRSamsung irSamsung;
LB_NRF24 nrf24;

void setup() {
  tv_rcHKTM.init();
  relaiCam.init();
  irSamsung.init();
  nrf24.init();

  roverHKTM.register((uint8_t *) tv_rcHKTM.getStateAddr(), sizeof(tv_rcHKTM.getState()));
  tv_rcHKTM.register((uint8_t *) relaiCam.getStateAddr(), sizeof(relaiCam.getState()));
}

void loop() {
  nrf24.run();
  if(true == nrf24.rxIsReady())
  {
    if(TV_RC_ID == nrf24.rxGetDst())
    {
      if(1 == nrf24.rxGetLen())
      {
        if(TV_RC_CMD_HKTM == nrf24.rxGetCmd()) { tv_rcHKTM.setState(nrf24.rxGetData()[0]); }
        if(TV_RC_CMD_CAM_POWER == nrf24.rxGetCmd()) { relaiCam.setState(nrf24.rxGetData()[0]); }
        if(TV_RC_CMD_IR_RAW_SAMSUNG == nrf24.rxGetCmd()) { irSamsung.set(nrf24.rxGetData()); }
        if(TV_RC_CMD_IR_MACRO_SAMSUNG_GO_HDMI1 == nrf24.rxGetCmd()) { irSamsung.set(); }
        if(TV_RC_CMD_IR_MACRO_SAMSUNG_GO_TV == nrf24.rxGetCmd()) { irSamsung.set(); }
      }
    }
    nrf24.rxRelease();
  }
  if(true == tv_rcHKTM.getState())
  {
    if(tv_rcHKTM.getLastTxTime() + 1000 < getCurrentTime())
    {
      if(true == nrf24.txIsReady())
      {
        tv_rcHKTM.refresh();
        nrf24.send(TV_RC_ID, LOST_ID, TV_RC_HKTM, ir_rc.getLen(), ir_rcHKTM.getData());
        ir_rcHKTM.setLastTxTime(getCurrentTime());
      }
    }
  }
}
