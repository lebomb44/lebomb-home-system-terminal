sudo avrdude -p m128 -P /dev/ttyS0 -c stk500v2 -V -U flash:w:../../main.hex
