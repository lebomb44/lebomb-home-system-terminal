#include <inttypes.h>
#include <Arduino.h>

//#include <ID/ID.h>
//#include <HomeEasy/HomeEasy.h>

//HomeEasy homeEasy; // OUT = B1(OC1A), IN = B0(ICP), MODE = D5, EN = D4

int main(void)
{
  //homeEasy.init();
  Serial.begin(9600);
  while(1)
  {
    //homeEasy.run();
    //if(true == homeEasy.rxCodeIsReady())
    {
    Serial.println();
    //Serial.print(homeEasy.rxGetCode(), HEX);Serial.print(" : ");
    //Serial.print(homeEasy.rxGetManufacturer(), HEX);Serial.print("-");
    //Serial.print(homeEasy.rxGetGroup(), HEX);Serial.print("-");
    /*Serial.print(homeEasy.rxGetDevice(), HEX);*/Serial.print("-");
    //Serial.print(homeEasy.rxGetStatus(), HEX);Serial.println();

    //homeEasy.rxRelease();
    }
  delay(1);        // delay in between reads for stability
  }
}

