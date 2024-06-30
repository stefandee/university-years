@ECHO ON
MD %1
CD %1
@ECHO OFF
:loop_label
  ..\meniu.exe
  if ERRORLEVEL 4 goto exit_label
  if ERRORLEVEL 3 type %2.srt
  if ERRORLEVEL 2 sort < %2.txt >%2.srt
  if ERRORLEVEL 1 copy con %2.txt
  PAUSE
goto loop_label

:exit_label
dir
cd..
PAUSE