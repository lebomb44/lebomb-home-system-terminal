#!/bin/bash
source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/node/ROOM
echo $PATH
make clean
export NODE_ROOM_CONFIG=mms_bureau
make all

