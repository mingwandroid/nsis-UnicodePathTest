call clean.bat

set nsis_path="%ProgramFiles%\NSIS\Unicode\makensis.exe"
@if not exist %nsis_path% @echo Unicode NSIS should be installed! & pause & goto :eof

%nsis_path% UnicodePathTest.nsi
pause