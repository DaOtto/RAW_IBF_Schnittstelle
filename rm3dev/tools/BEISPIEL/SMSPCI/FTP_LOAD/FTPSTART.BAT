rem ---- change to debug directory with loadable file ----
cd %1

rem ---- create ftplog.txt ----
echo put %3>%2\ftplog2.txt
copy /b %2\ftplog1.txt+%2\ftplog2.txt+%2\ftplog3.txt %2\ftplog.txt

rem ---- copy loadable file to target system ----
rem ---- environment of FTPD has to be set!!!     ----
rem ---- passwd has to be set to <root;;0;0;c:\;> ---
ftp <%2\ftplog.txt

rem ---- delete temporary files ----
if exist %2\ftplog.txt del %2\ftplog.txt
if exist %2\ftplog2.txt del %2\ftplog2.txt
