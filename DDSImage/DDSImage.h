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

		BitmapSource^ Load(System::String^ path);

	private:
		DDSTexture* _impl = nullptr;
	};
}


