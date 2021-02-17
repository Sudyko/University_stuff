:: Simple bat-script for grab amount of processes [ Windows ]
@echo off
:begin
tasklist | find /v /n /c "" >> tripple.txt
goto begin
