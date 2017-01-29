/*****************************************************************
 *           NSIS plugin UnicodePathTest v1.0                    *
 *                    ( for Unicode NSIS )                       *
 *         2011 Marek Mizanin aka Zanir (zanir@szm.sk)           *
 *****************************************************************/

- plugin work only with Unicode version of NSIS
- it is under LGPL licence

Installing:
- copy UnicodePathTest.dll to c:\Program Files\NSIS\Unicode\Plugins

Using:
- call UnicodePathTest::UnicodePathTes function in your .nsi

Example:
UnicodePathTest::UnicodePathTest "path"
Pop $var

"path"
 - input string 

$var is
- "unicode" if path contains unicode characters
- "ascii" if path not contains unicode characters

- take a look at examples -> Example\UnicodePathTest.nsi