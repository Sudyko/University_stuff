:: Simple bat-script for grabbing info about amount of processes [ Windows ]
@echo off
:begin
tasklist | find /v /n /c "" >> tripple.txt
goto begin