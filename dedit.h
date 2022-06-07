#pragma once
#include <string>

const int gameCount = 4;

const int DEditAddresses[] =	
									{ 
									0x41F5EE, //AVP2
									0x42E889, //BLOOD2
									0x41FAB8, //NOLF
									0x41C3A7, //KISS
									};
const int DEditChecksums[] = 
									{ 
									1414032, //AVP2
									657521, //BLOOD2
									1361200, //NOLF
									1551811 //KISS
									};

//Define our functions
typedef signed int(__cdecl* _CheckTextureSize)(int a1);
_CheckTextureSize CheckTextureSize_Original;

//Valid sizes of textures to accept
const int g_ValidTextureSizes[10] = { 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8 };

//Functions
void HookFunctions();
void InitializeDLL();
signed int __cdecl CheckTextureSize_New(int a1);
void GetFileChecksum();
int GetAddressOffset(int checksum);