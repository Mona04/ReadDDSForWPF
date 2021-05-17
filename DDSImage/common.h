#pragma once
#pragma comment(lib, "User32.lib") 
#pragma comment(lib, "Gdi32.lib") 
#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "Impl.lib")
#ifdef _DEBUG
#pragma comment (lib, "DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex_release.lib")
#endif

#include <msclr/marshal_cppstd.h>
#include <atlcoll.h>
#using <WindowsBase.dll>
#using <PresentationCore.dll>