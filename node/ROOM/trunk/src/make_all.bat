CALL env.bat
%DEVBASE_DRIVE%
cd %DEVBASE%/NODE_ROOM
SET PATH=%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/utils/bin;%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/bin;%PATH%
PATH
make clean
make all
pause
