CALL env.bat
%DEVBASE_DRIVE%
cd %DEVBASE%/NODE_REMOTE
SET PATH=%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/utils/bin;%DEVBASE%/COMPILER/AVR-GCC/%COMPILER_VERSION%/bin
PATH
make clean
make burn
pause
