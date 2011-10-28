CALL ../env.bat
%DEVBASE_DRIVE%
cd %DEVBASE%/App
SET PATH=%DEVBASE%/OS/ethernut-4.8.3/nut/tools/win32;%DEVBASE%/Compiler/WinAVR_20090313/Portable/WinAVR-20090313/utils/bin;%DEVBASE%/Compiler/WinAVR_20090313/Portable/WinAVR-20090313/bin;%PATH%
PATH
make clean
make all
pause
