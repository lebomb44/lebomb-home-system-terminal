source ../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/NODE_REMOTE
echo $PATH
make clean
export NODE_REMOTE_CONFIG=c1
make all

