CALL ../../env.bat
%DEVBASE_DRIVE%
cd %DEVBASE%/node/ROOM
SET PATH=%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/utils/bin;%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/bin
PATH
make clean
SET NODE_ROOM_CONFIG=mms_couloir
make all
pause
