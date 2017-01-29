/*****************************************************************
 *           NSIS plugin UnicodePathTest v1.0                    *
 *                    ( for Unicode NSIS )                       *
 *         2011 Marek Mizanin aka Zanir (zanir@szm.sk)           *
 *****************************************************************/

#define UNICODE
#define _UNICODE
#include <windows.h>
#include "nsis/pluginapi.h" // nsis plugin
#pragma comment(lib,"__FILE__\\..\\nsis\\pluginapi.lib")

HINSTANCE g_hInstance;
HWND g_hwndParent;

void __UnicodePathTest(wchar_t *sIn)
{
	char *pBufferMultiByteAcp = NULL;
	char *pBufferMultiByteUtf8 = NULL;
	char *pBufferMultiByteMy = NULL;
	int nSize;
	int nLen;
	int i;

	nLen = lstrlenW(sIn);
	if(!nLen)
	{
		pushstring(L"unicode");
		return;
	}

	nSize = WideCharToMultiByte(CP_UTF8, 0, sIn, -1, NULL, 0, NULL, NULL);		// get multi byte size
	pBufferMultiByteUtf8 = (char*)GlobalAlloc(GPTR, nSize);

	// use WideCharToMultiByte to get multi byte char*
	if(WideCharToMultiByte(CP_UTF8, 0, sIn, -1, pBufferMultiByteUtf8, nSize, NULL, NULL) == 0)
	{
		GlobalFree(pBufferMultiByteUtf8);
		pushstring(L"unicode");
		return;
	}
	// create own multi byte version of string
	pBufferMultiByteMy = (char*)GlobalAlloc(GPTR, nLen+1);
	for(i=0; i<nLen; i++)
		pBufferMultiByteMy[i] = sIn[i] < 128 ? sIn[i] : 0;

	// compare if are the same
	if(lstrcmpA(pBufferMultiByteUtf8, pBufferMultiByteMy) == 0)
		pushstring(L"ascii");	// ok string not contain Unicode characters
	else
	{
		// CP_ACP?
		nSize = WideCharToMultiByte(CP_ACP, 0, sIn, -1, NULL, 0, NULL, NULL);		// get ACP size
		pBufferMultiByteAcp = (char*)GlobalAlloc(GPTR, nSize);

		// use WideCharToMultiByte to get ACP char*
		if(WideCharToMultiByte(CP_ACP, 0, sIn, -1, pBufferMultiByteAcp, nSize, NULL, NULL) == 0)
		{
			GlobalFree(pBufferMultiByteAcp);
			pushstring(L"unicode");
			return;
		}
		for(i=0; i<nLen; i++)
			pBufferMultiByteMy[i] = sIn[i] < 256 ? sIn[i] : 0;
		// compare if are the same
		if(lstrcmpA(pBufferMultiByteAcp, pBufferMultiByteMy) == 0)
			pushstring(L"ascii_cp_acp");	// ok string not contain Unicode characters
		else
			pushstring(L"unicode");
		GlobalFree(pBufferMultiByteAcp);
	}

	GlobalFree(pBufferMultiByteUtf8);
	GlobalFree(pBufferMultiByteMy);
}


void __declspec(dllexport) UnicodePathTest(HWND hwndParent, int string_size, 
                                      TCHAR *variables, stack_t **stacktop,
                                      extra_parameters *extra)
{
	wchar_t sIn[1024];
	
	g_hwndParent=hwndParent;
	EXDLL_INIT();

	// note if you want parameters from the stack, pop them off in order.
	// i.e. if you are called via exdll::myFunction file.dat poop.dat
	// calling popstring() the first time would give you file.dat,
	// and the second time would give you poop.dat. 
	// you should empty the stack of your parameters, and ONLY your
	// parameters.

	popstring(sIn);
	if (sIn[0] == 0)
	{
		pushstring(L"unicode");
		return;
	}

	__UnicodePathTest(sIn);
}

BOOL __stdcall DllMain(HANDLE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	g_hInstance=hInst;
	return TRUE;
}
