del arcade64.sym
:start
del arcade64.exe
if exist arcade64.exe goto start
make64 -j4 %1 %2 %3
copy /Y arcade64.exe arcade.exe

