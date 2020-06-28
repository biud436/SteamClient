// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char* pchDebugText)
{
	// if you're running in the debugger, only warnings (nSeverity >= 1) will be sent
	// if you add -debug_steamapi to the command-line, a lot of extra informational messages will also be sent
	::OutputDebugStringA(pchDebugText);

	if (nSeverity >= 1)
	{
		// place to set a breakpoint for catching API errors
		int x = 3;
		(void)x;
	}
}

#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) void sendCommand(const char* command)
	{
		return;
	}

#ifdef __cplusplus
}
#endif

void InitWithSteamAPI() 
{
	// 1334420 k_uAppIdInvalid
	if (SteamAPI_RestartAppIfNecessary(1334420))
	{
		return;
	}

	if (!SteamAPI_Init())
	{
		MessageBoxW(NULL, L"Steam API initialization failed", L"Warning", MB_OK | MB_ICONERROR);
		return;
	}

	// set our debug handler
	SteamClient()->SetWarningMessageHook(&SteamAPIDebugTextHook);

	if (!SteamUser()->BLoggedOn())
	{
		MessageBoxW(NULL, L"Steam user must be logged in to play this game (SteamUser()->BLoggedOn() returned false).\n", L"Warning", MB_OK | MB_ICONERROR);
		return;
	}

	if (!SteamInput()->Init())
	{
		MessageBoxW(NULL, L"SteamInput()->Init failed.\n", L"Warning", MB_OK | MB_ICONERROR);
		return;
	}
}

void DisposeSteamAPI()
{
	SteamAPI_Shutdown();
}