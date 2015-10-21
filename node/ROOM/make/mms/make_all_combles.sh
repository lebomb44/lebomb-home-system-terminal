source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/node/ROOM
echo $PATH
make clean
export NODE_REMOTE_CONFIG=mms_combles
make all

