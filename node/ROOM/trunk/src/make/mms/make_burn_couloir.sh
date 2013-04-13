source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/NODE_ROOM
echo $PATH
make clean
export NODE_REMOTE_CONFIG=mms_couloir
make burn

