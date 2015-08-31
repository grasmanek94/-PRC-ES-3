@echo off
cd /D "%~dp0"
for /f "delims=\" %%a in ("%~dp0") do SET executable="%%~nxa_test"
set PATH=%CYGWIN64%\usr\bin;%CYGWIN64%\bin;%CYGWIN64%\usr\sbin;%CYGWIN64%\usr\local\bin;
%executable%
echo(
echo Application exitted with code %errorlevel%
pause