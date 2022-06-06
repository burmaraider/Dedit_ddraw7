#include <windows.h>
#include <detours.h>
#include "dedit.h"
#include <imagehlp.h>
#pragma comment( lib, "imagehlp.lib" )

int fileChecksum;

struct ddraw_dll { 
	HMODULE dll;
	FARPROC OrignalAcquireDDThreadLock;
	FARPROC OrignalCompleteCreateSysmemSurface;
	FARPROC OrignalD3DParseUnknownCommand;
	FARPROC OrignalDDGetAttachedSurfaceLcl;
	FARPROC OrignalDDInternalLock;
	FARPROC OrignalDDInternalUnlock;
	FARPROC OrignalDSoundHelp;
	FARPROC OrignalDirectDrawCreate;
	FARPROC OrignalDirectDrawCreateClipper;
	FARPROC OrignalDirectDrawCreateEx;
	FARPROC OrignalDirectDrawEnumerateA;
	FARPROC OrignalDirectDrawEnumerateExA;
	FARPROC OrignalDirectDrawEnumerateExW;
	FARPROC OrignalDirectDrawEnumerateW;
	FARPROC OrignalDllCanUnloadNow;
	FARPROC OrignalDllGetClassObject;
	FARPROC OrignalGetDDSurfaceLocal;
	FARPROC OrignalGetOLEThunkData;
	FARPROC OrignalGetSurfaceFromDC;
	FARPROC OrignalRegisterSpecialCase;
	FARPROC OrignalReleaseDDThreadLock;
	FARPROC OrignalSetAppCompatData;
} ddraw;

__declspec(naked) void FakeAcquireDDThreadLock() { _asm { jmp[ddraw.OrignalAcquireDDThreadLock] } }
__declspec(naked) void FakeCompleteCreateSysmemSurface() { _asm { jmp[ddraw.OrignalCompleteCreateSysmemSurface] } }
__declspec(naked) void FakeD3DParseUnknownCommand() { _asm { jmp[ddraw.OrignalD3DParseUnknownCommand] } }
__declspec(naked) void FakeDDGetAttachedSurfaceLcl() { _asm { jmp[ddraw.OrignalDDGetAttachedSurfaceLcl] } }
__declspec(naked) void FakeDDInternalLock() { _asm { jmp[ddraw.OrignalDDInternalLock] } }
__declspec(naked) void FakeDDInternalUnlock() { _asm { jmp[ddraw.OrignalDDInternalUnlock] } }
__declspec(naked) void FakeDSoundHelp() { _asm { jmp[ddraw.OrignalDSoundHelp] } }
__declspec(naked) void FakeDirectDrawCreate() { _asm { jmp[ddraw.OrignalDirectDrawCreate] } }
__declspec(naked) void FakeDirectDrawCreateClipper() { _asm { jmp[ddraw.OrignalDirectDrawCreateClipper] } }
__declspec(naked) void FakeDirectDrawCreateEx() { _asm { jmp[ddraw.OrignalDirectDrawCreateEx] } }
__declspec(naked) void FakeDirectDrawEnumerateA() { _asm { jmp[ddraw.OrignalDirectDrawEnumerateA] } }
__declspec(naked) void FakeDirectDrawEnumerateExA() { _asm { jmp[ddraw.OrignalDirectDrawEnumerateExA] } }
__declspec(naked) void FakeDirectDrawEnumerateExW() { _asm { jmp[ddraw.OrignalDirectDrawEnumerateExW] } }
__declspec(naked) void FakeDirectDrawEnumerateW() { _asm { jmp[ddraw.OrignalDirectDrawEnumerateW] } }
__declspec(naked) void FakeDllCanUnloadNow() { _asm { jmp[ddraw.OrignalDllCanUnloadNow] } }
__declspec(naked) void FakeDllGetClassObject() { _asm { jmp[ddraw.OrignalDllGetClassObject] } }
__declspec(naked) void FakeGetDDSurfaceLocal() { _asm { jmp[ddraw.OrignalGetDDSurfaceLocal] } }
__declspec(naked) void FakeGetOLEThunkData() { _asm { jmp[ddraw.OrignalGetOLEThunkData] } }
__declspec(naked) void FakeGetSurfaceFromDC() { _asm { jmp[ddraw.OrignalGetSurfaceFromDC] } }
__declspec(naked) void FakeRegisterSpecialCase() { _asm { jmp[ddraw.OrignalRegisterSpecialCase] } }
__declspec(naked) void FakeReleaseDDThreadLock() { _asm { jmp[ddraw.OrignalReleaseDDThreadLock] } }
__declspec(naked) void FakeSetAppCompatData() { _asm { jmp[ddraw.OrignalSetAppCompatData] } }

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	char path[MAX_PATH];
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CopyMemory(path + GetSystemDirectory(path, MAX_PATH - 11), "\\ddraw.dll", 11);
		ddraw.dll = LoadLibrary(path);
		if (!ddraw.dll)
		{
			MessageBox(0, "Cannot load original ddraw.dll library", "Proxy", MB_ICONERROR);
			ExitProcess(0);
		}
		else
		{
			OutputDebugStringA("Original ddraw.dll successfully loaded");
			ddraw.OrignalAcquireDDThreadLock = GetProcAddress(ddraw.dll, "AcquireDDThreadLock");
			ddraw.OrignalCompleteCreateSysmemSurface = GetProcAddress(ddraw.dll, "CompleteCreateSysmemSurface");
			ddraw.OrignalD3DParseUnknownCommand = GetProcAddress(ddraw.dll, "D3DParseUnknownCommand");
			ddraw.OrignalDDGetAttachedSurfaceLcl = GetProcAddress(ddraw.dll, "DDGetAttachedSurfaceLcl");
			ddraw.OrignalDDInternalLock = GetProcAddress(ddraw.dll, "DDInternalLock");
			ddraw.OrignalDDInternalUnlock = GetProcAddress(ddraw.dll, "DDInternalUnlock");
			ddraw.OrignalDSoundHelp = GetProcAddress(ddraw.dll, "DSoundHelp");
			ddraw.OrignalDirectDrawCreate = GetProcAddress(ddraw.dll, "DirectDrawCreate");
			ddraw.OrignalDirectDrawCreateClipper = GetProcAddress(ddraw.dll, "DirectDrawCreateClipper");
			ddraw.OrignalDirectDrawCreateEx = GetProcAddress(ddraw.dll, "DirectDrawCreateEx");
			ddraw.OrignalDirectDrawEnumerateA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateA");
			ddraw.OrignalDirectDrawEnumerateExA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExA");
			ddraw.OrignalDirectDrawEnumerateExW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExW");
			ddraw.OrignalDirectDrawEnumerateW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateW");
			ddraw.OrignalDllCanUnloadNow = GetProcAddress(ddraw.dll, "DllCanUnloadNow");
			ddraw.OrignalDllGetClassObject = GetProcAddress(ddraw.dll, "DllGetClassObject");
			ddraw.OrignalGetDDSurfaceLocal = GetProcAddress(ddraw.dll, "GetDDSurfaceLocal");
			ddraw.OrignalGetOLEThunkData = GetProcAddress(ddraw.dll, "GetOLEThunkData");
			ddraw.OrignalGetSurfaceFromDC = GetProcAddress(ddraw.dll, "GetSurfaceFromDC");
			ddraw.OrignalRegisterSpecialCase = GetProcAddress(ddraw.dll, "RegisterSpecialCase");
			ddraw.OrignalReleaseDDThreadLock = GetProcAddress(ddraw.dll, "ReleaseDDThreadLock");
			ddraw.OrignalSetAppCompatData = GetProcAddress(ddraw.dll, "SetAppCompatData");


			//Start hooking functions

			InitializeDLL();
		}

		break;
	}
	case DLL_PROCESS_DETACH:
	{
		FreeLibrary(ddraw.dll);
	}
	break;
	}
	return TRUE;
}

void HookFunctions()
{
	if (fileChecksum != 0)
	{
		static bool once = true; if (once) {
			once = false;

			CheckTextureSize_Original = (_CheckTextureSize)(GetAddressOffset(fileChecksum));
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&(PVOID&)CheckTextureSize_Original, CheckTextureSize_New);
			if (DetourTransactionCommit() == NO_ERROR)
			{
				OutputDebugStringA("Successfully detoured function\n");
			}
			else
			{
				OutputDebugStringA("Could not detour function!\n");
			}
		}
	}
}

void InitializeDLL()
{
	GetFileChecksum();
	//Do things here
	HookFunctions();
}

signed int __cdecl CheckTextureSize_New(int a1)
{
	int i = 0;
	while (a1 != g_ValidTextureSizes[i])
	{
		if (a1 >= 8)
			i++;
		else
			return 0;
	}
	return 1;

}

void GetFileChecksum()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	PDWORD header = (PDWORD)malloc(sizeof(PDWORD));
	PDWORD check = (PDWORD)malloc(sizeof(PDWORD));

	if (header != nullptr && check != nullptr)
	{
		MapFileAndCheckSum(buffer, header, check);
	}

	if(check != nullptr)
		fileChecksum = *check;
	free(header);
	free(check);
}

int GetAddressOffset(int checksum)
{
	for (size_t i = 0; i < gameCount; i++)
	{
		if (checksum == DEditVersions[i])
		{
			return DEditAddresses[i];
		}
	}
	return 0;
}