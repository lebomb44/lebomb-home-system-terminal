source env.sh
echo $DEVBASE_DRIVE
cd $DEVBASE/APP
export PATH=$DEVBASE/OS/$OS_VERSION/nut/tools/win32:$DEVBASE/COMPILER/$COMPILER_VERSION/utils/bin:$DEVBASE/COMPILER/$COMPILER_VERSION/bin
echo $PATH
make clean
make burn
