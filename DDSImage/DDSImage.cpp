#include "DDSImage.h"

typedef unsigned int uint;

DDSImage::DDSImage::DDSImage()
{
	_impl = new DDSTexture();
}

DDSImage::DDSImage::~DDSImage()
{
	delete _impl;
}

BitmapSource^ DDSImage::DDSImage::Load(System::String^ path)
{
	bool r = _impl->LoadTexture(marshal_as<std::wstring>(path));
	
    PixelFormat format;
    switch (_impl->channel) {
    case 1: 
        switch (_impl->bpc) {
        case 8:  format = PixelFormats::Gray8; break;
        case 16: format = PixelFormats::Gray16; break;
        case 32: format = PixelFormats::Gray32Float; break;
        } break;
    case 3: format = PixelFormats::Bgr32; break;
        switch (_impl->bpc) {
        case 8:  format = PixelFormats::Bgr32; break;
        case 16: format = PixelFormats::Rgb48; break;
        } break;
    case 4:
        switch (_impl->bpc) {
        case 8:  format = PixelFormats::Bgra32; break;
        case 16: format = PixelFormats::Rgba64; break;
        case 32: format = PixelFormats::Rgba128Float; break;
        } break;
    }
    
    WriteableBitmap^ wbm = gcnew WriteableBitmap(_impl->width, _impl->height, 96, 96, format, nullptr);
    CopyMemory(wbm->BackBuffer.ToPointer(), _impl->data, (uint)(_impl->width * _impl->height * _impl->channel));
    auto k = ((int*)(wbm->BackBuffer.ToPointer()))[0];

    wbm->Lock();
    wbm->AddDirtyRect(Int32Rect(0, 0, wbm->PixelWidth, wbm->PixelHeight));
    wbm->Unlock();

    return wbm;
}
