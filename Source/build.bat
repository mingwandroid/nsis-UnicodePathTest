if exist UnicodePathTest.dll del UnicodePathTest.dll

call "%VS80COMNTOOLS%vsvars32"
cl /O1 UnicodePathTest.c /LD kernel32.lib user32.lib /link /ENTRY:DllMain /OPT:NOWIN98

@echo off
rem clean no necessary files
if exist UnicodePathTest.obj del UnicodePathTest.obj
if exist UnicodePathTest.exp del UnicodePathTest.exp
if exist UnicodePathTest.lib del UnicodePathTest.lib
pause