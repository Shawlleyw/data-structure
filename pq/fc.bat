@echo off
:loop
datamaker.exe
test.exe
std.exe
fc data.out std.out
if errorlevel == 0 (goto loop) else (pause)
