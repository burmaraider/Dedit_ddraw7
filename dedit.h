#pragma once
#include <string>

const int gameCount = 3;

extern const int DEditAddresses[] =		{ 0x41F5EE, 0x42E889, 0x41FAB8 };
extern const int DEditVersions[] =		{ 1414032, 657521, 1361200 };

//Define our functions
typedef signed int(__cdecl* _CheckTextureSize)(int a1);
_CheckTextureSize CheckTextureSize_Original;

//Valid sizes of textures to accept
extern const int g_ValidTextureSizes[10] = { 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8 };

//Functions
void HookFunctions();
void InitializeDLL();
signed int __cdecl CheckTextureSize_New(int a1);
void GetFileChecksum();
int GetAddressOffset(int checksum);