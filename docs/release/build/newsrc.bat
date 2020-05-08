set from=C:\ARCADE
set to=c:\ARCADE\docs\release

rd %to%\src /q /s

md %to%\src\devices\machine
copy /Y %from%\src\devices\machine\idehd.cpp        %to%\src\devices\machine

md %to%\src\devices\sound
copy /Y %from%\src\devices\sound\qs1000.cpp         %to%\src\devices\sound

md %to%\src\devices\cpu\psx
copy /Y %from%\src\devices\cpu\psx\irq.cpp          %to%\src\devices\cpu\psx

md %to%\src\emu
copy /Y %from%\src\emu\emuopts.*                    %to%\src\emu
copy /Y %from%\src\emu\inpttype.h                   %to%\src\emu
copy /Y %from%\src\emu\ioport.h                     %to%\src\emu
copy /Y %from%\src\emu\render.cpp                   %to%\src\emu
copy /Y %from%\src\emu\video.*                      %to%\src\emu

md %to%\src\frontend\mame\ui
copy /Y %from%\src\frontend\mame\audit.*            %to%\src\frontend\mame
copy /Y %from%\src\frontend\mame\language.cpp       %to%\src\frontend\mame
copy /Y %from%\src\frontend\mame\ui\datmenu.cpp     %to%\src\frontend\mame\ui
copy /Y %from%\src\frontend\mame\ui\mainmenu.cpp    %to%\src\frontend\mame\ui
copy /Y %from%\src\frontend\mame\ui\submenu.cpp     %to%\src\frontend\mame\ui
copy /Y %from%\src\frontend\mame\ui\menu.cpp        %to%\src\frontend\mame\ui
copy /Y %from%\src\frontend\mame\ui\ui.*            %to%\src\frontend\mame\ui
copy /Y %from%\src\frontend\mame\ui\text.h          %to%\src\frontend\mame\ui

md %to%\src\mame\drivers
md %to%\src\mame\includes
md %to%\src\mame\machine
md %to%\src\mame\video
copy /Y %from%\src\mame\arcade.flt                  %to%\src\mame
copy /Y %from%\src\mame\mame.lst                    %to%\src\mame
copy /Y %from%\src\mame\drivers\aliens.cpp          %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\astrocde.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\btime.cpp           %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\cave.cpp            %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\citycon.cpp         %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\cps1.cpp            %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\crimfght.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\deniam.cpp          %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\gberet.cpp          %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\gng.cpp             %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\jailbrek.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\m72.cpp             %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\megasys1.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\midas.cpp           %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\mystwarr.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\namconb1.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\nemesis.cpp         %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\neodriv.hxx         %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\neogeo.cpp          %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\pgm.cpp             %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\polepos.cpp         %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\scregg.cpp          %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\simpsons.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\ssv.cpp             %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\thunderx.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\vegas.cpp           %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\vendetta.cpp        %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\xmen.cpp            %to%\src\mame\drivers
copy /Y %from%\src\mame\video\cidelsa.cpp           %to%\src\mame\video
copy /Y %from%\src\mame\video\cps1.cpp              %to%\src\mame\video
copy /Y %from%\src\mame\video\mystwarr.cpp          %to%\src\mame\video
copy /Y %from%\src\mame\video\namconb1.cpp          %to%\src\mame\video
copy /Y %from%\src\mame\video\nemesis.cpp           %to%\src\mame\video
copy /Y %from%\src\mame\video\neogeo.cpp            %to%\src\mame\video
copy /Y %from%\src\mame\video\neogeo_spr.h          %to%\src\mame\video
copy /Y %from%\src\mame\video\tc0100scn.cpp         %to%\src\mame\video


md %to%\src\osd\modules\lib
md %to%\src\osd\modules\render
copy /Y %from%\src\osd\modules\osdwindow.h          %to%\src\osd\modules
copy /Y %from%\src\osd\modules\lib\osdobj_common.*  %to%\src\osd\modules\lib
copy /Y %from%\src\osd\modules\render\drawogl.cpp   %to%\src\osd\modules\render

md %to%\src\osd\windows
copy /Y %from%\src\osd\windows\video.cpp            %to%\src\osd\windows
copy /Y %from%\src\osd\windows\winmain.*            %to%\src\osd\windows

md %to%\src\osd\winui
xcopy /E /Y %from%\src\osd\winui                    %to%\src\osd\winui

md %to%\src\osd\modules\render
copy /Y %from%\src\osd\modules\render\drawd3d.cpp   %to%\src\osd\modules\render

rem now save all our stuff to github
copy %from%\*.bat                                   %to%\build
xcopy /E /Y %from%\scripts                          %to%\scripts

