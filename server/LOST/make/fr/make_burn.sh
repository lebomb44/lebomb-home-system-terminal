source ../../env.sh
cd $DEVBASE_DRIVE
cd $DEVBASE/LOST
echo $PATH
make clean
export LOST_CONFIG=fr
make burn

