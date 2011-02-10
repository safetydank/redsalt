@echo off

setlocal

PATH=%~dp0..\..\third_party\cygwin\bin;%PATH%

make.exe %*
