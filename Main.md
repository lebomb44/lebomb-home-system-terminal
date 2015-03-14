# Introduction #

Welcome to the LOST project (LeBomb hOme System Terminal).
This project is dedicated to home automation.



# Details #

This is based on a simple concept:
  * [A centralized board : LOST Server](LOST_Server_Main.md)
  * [Some intelligent nodes : LOST Node](LOST_Nodes_Main.md)

Everything is accessible through a Web Interface

The centralized board is in charge of :
  * [Home Safety.](http://en.wikipedia.org/wiki/Home_safety)
  * [Home Security.](http://en.wikipedia.org/wiki/Security)
  * Alert ([GSM](http://en.wikipedia.org/wiki/GSM), [Email](http://en.wikipedia.org/wiki/Email), Buzzer)
  * Scenario management
  * Command and Control dispatch

# Architecture #
All the system is based on a [I2C bus](http://en.wikipedia.org/wiki/I%C2%B2C). It has many advantages :
  * Standard
  * Low Cost
  * Widely used
  * Short cut tolerant

![http://lebomb-home-system-terminal.googlecode.com/svn/wiki/Images/LOST_Archi.jpg](http://lebomb-home-system-terminal.googlecode.com/svn/wiki/Images/LOST_Archi.jpg)