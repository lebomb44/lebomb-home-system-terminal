source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/server/LOST
echo $PATH
make clean
export LOST_CONFIG=fr
make burn

