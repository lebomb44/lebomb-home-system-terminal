#!/bin/bash
source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/NODE_ROOM
echo $PATH
make clean
export NODE_ROOM_CONFIG=mms_terrasse
make all

