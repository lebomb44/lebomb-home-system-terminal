source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/NODE_REMOTE
echo $PATH
make clean
export NODE_REMOTE_CONFIG=global
make burn

