#include <iostream>
#include "../Impl/DDS.h"
#pragma comment (lib, "Impl.lib")
#ifdef _DEBUG
#pragma comment (lib, "DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex_release.lib")
#endif
#include "../Impl/FileSystem.h"

int main()
{
    DDSTexture tex;
    tex.LoadTexture(L"../SampleTex/Sample.dds", 10, -1);  
}
