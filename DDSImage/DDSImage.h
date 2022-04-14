#pragma once
#include "common.h"
#include "../Impl/DDS.h"

using namespace System::Windows;
using namespace System::Windows::Media;
using namespace System::Windows::Media::Imaging;
using namespace msclr::interop;

namespace DDSImage {
	public ref class DDSImage
	{
	public:
		DDSImage();
		~DDSImage();

		// if one of width and height is -1, resize using other value with original widht/height ratio.
		// But all of width and height is -1, a exception is thrown.
		BitmapSource^ Load(System::String^ path, int width, int height);
		static bool IsSupported(System::String^ path);
		
	private:
		DDSTexture* _impl = nullptr;
	};
}


