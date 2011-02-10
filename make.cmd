setlocal

PATH=%~dp0.\native_client_sdk\third_party\cygwin\bin;%PATH%

make.exe %*
