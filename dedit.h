//Address of the texture size checking function in Dedit.exe
const int checkTextureFunctionOffset = 0x41F5EE;

//Define our functions
typedef signed int(__cdecl* _CheckTextureSize)(int a1);
_CheckTextureSize CheckTextureSize_Original;

//Valid sizes of textures to accept
extern const int g_ValidTextureSizes[10] = { 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8 };

//Functions
void HookFunctions();
void InitializeDLL();
signed int __cdecl CheckTextureSize_New(int a1);