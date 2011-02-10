REM Relative path of CygWin
set CYGWIN=%~dp0%.\native_client_sdk\third_party\cygwin\bin

PATH=%CYGWIN%;%PATH%

python httpd.py
