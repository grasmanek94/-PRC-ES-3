@echo off
cd /D "%~dp0"
set PATH=%PROFTAAK_T31_CROSS_COMPILE_BIN%;%PATH%
make clean
make all
