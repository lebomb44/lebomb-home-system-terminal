CALL ../../env.bat
%DEVBASE_DRIVE%
cd %DEVBASE%/server/LOST/trunk/LOST
SET PATH=%DEVBASE%/OS/Ethernut/%OS_VERSION%/nut/tools/win32;%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/utils/bin;%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/bin
PATH
make clean
SET LOST_CONFIG=lb
make burn
pause
