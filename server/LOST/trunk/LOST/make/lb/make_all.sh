source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/server/LOST/trunk/LOST
echo $PATH
make clean
export LOST_CONFIG=lb
make all

