avrdude -p m8 -P /dev/ttyS0 -c stk500v2 -U hfuse:w:hfuse.bin:r
avrdude -p m8 -P /dev/ttyS0 -c stk500v2 -U lfuse:w:lfuse.bin:r

