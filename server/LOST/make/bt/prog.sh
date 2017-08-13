sudo avrdude -p m128 -P /dev/ttyUSB0 -c stk500v2 -V -U flash:w:../../main.hex
