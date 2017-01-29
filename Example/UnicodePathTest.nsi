/*****************************************************************
 *           NSIS plugin UnicodePathTest v1.0                    *
 *                                                               *
 *         2011 Marek Mizanin aka Zanir (zanir@szm.sk)           *
 *****************************************************************/

/*
	Test for unicode path
	
	UnicodePathTest::UnicodePathTest "path"
	Pop $var
	
	$var:
	  "unicode" - path contains unicode chars
	  "ascii" - path doesn't contain unicode chars
*/

;Include Modern UI
!include "MUI2.nsh"

Name "UnicodePathTest"
OutFile "UnicodePathTest.exe"
InstallDir "$PROGRAMFILES\Unicode path test ú"

; define function on leaving page directory dialog
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE DirectoryLeave
!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

Section
SectionEnd

; function which check path and show message box
Function DirectoryLeave
	; test if path contains unicode characters
	UnicodePathTest::UnicodePathTest $INSTDIR
	Pop $R1
	
	StrCmp $R1 "ascii"  ascii_path
    messagebox mb_ok 'Path cannot contain special characters or diacritics!'
    abort

ascii_path:
	messagebox mb_ok 'Path is ok!'			; only for this example, remove in release
	
FunctionEnd