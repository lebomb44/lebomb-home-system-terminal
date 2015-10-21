source ../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/node/REMOTE
echo $PATH
make clean
export NODE_REMOTE_CONFIG=c1
make burn

