# Introduction #

The board is organized around an ATMega8L.
![http://lebomb-home-system-terminal.googlecode.com/svn/wiki/LOST_Nodes/Room/Hw/Images/Room_Hw_Top.jpg](http://lebomb-home-system-terminal.googlecode.com/svn/wiki/LOST_Nodes/Room/Hw/Images/Room_Hw_Top.jpg)

# Details #

As you can see on the picture, the board has:
  * A micro-controller ATMega8L
  * Power function:
    * A power regulator DC-DC 12V to 5V. Ref : TEL 5-1211
    * A power regulation 12V to 9 V. Ref : 78L09A0
  * An RJ45 connector:
    * I2C bus
    * 12V Power
  * Infra-red function:
    * FET transistor. Ref : BSS170
    * An IR LED. Ref : OPKBL53F3C
  * Shutter management:
    * Acquisitions:
      * Up Button through diode to GND. Ref : 1N4001
      * Down Button through diode to GND. Ref : 1N4001
    * Commands:
      * Motor power Up. 1 opto-couplers. Ref : 4N46 + 1 relay. Ref : Finder 41.52.9.012.0010
      * Motor power down. 1 opto-couplers. Ref : 4N46 + 1 relay. Ref : Finder 41.52.9.012.0010
  * Alarm Acquisitions:
    * Movement detector
    * Window detector
    * Shutter detector
    * Temperature detector (see on the bottom face)
    * Smoke detector (see on the bottom face)

# Printed Circuit Board #

The bottom face of the Node.
![http://lebomb-home-system-terminal.googlecode.com/svn/wiki/LOST_Nodes/Room/Hw/Images/Room_Hw_Bottom.jpg](http://lebomb-home-system-terminal.googlecode.com/svn/wiki/LOST_Nodes/Room/Hw/Images/Room_Hw_Bottom.jpg)

Connection to the smoke detector.
![http://lebomb-home-system-terminal.googlecode.com/svn/wiki/LOST_Nodes/Room/Hw/Images/Room_Hw_Smoke.jpg](http://lebomb-home-system-terminal.googlecode.com/svn/wiki/LOST_Nodes/Room/Hw/Images/Room_Hw_Smoke.jpg)