@echo off
set MINGW32=E:\Mingw\5-3-0\mingw32
set minpath=%MINGW32%\bin
set oldpath=%Path%
set Path=%minpath%;%oldpath%
echo.|time
%MINGW32%\bin\make PTR64=0 SUBTARGET=arcade OSD=winui SYMBOLS=0 NO_SYMBOLS=1 %1 %2 %3 %4
echo.|time
set Path=%oldpath%
set oldpath=
if exist arcade32.exe %minpath%\strip -s arcade32.exe
set minpath=

