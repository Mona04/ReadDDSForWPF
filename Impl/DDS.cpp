#define NOMINMAX
#include "DDS.h"
#include "FileSystem.h"
#include <string>
#include <algorithm>

int DDSTexture::max_extract_mip_level = 3;

DDSTexture::DDSTexture()
{
	image = new DirectX::ScratchImage();
}

DDSTexture::~DDSTexture()
{
	delete image;
}

bool DDSTexture::LoadTexture(std::wstring_view path)
{
    if (FileSystem::IsExistFile(path) == false)
        return false;
    if (FileSystem::GetExtension(path) != L"dds")
        return false;

    auto hr = DirectX::LoadFromDDSFile(path.data(),
        DirectX::DDS_FLAGS::DDS_FLAGS_FORCE_RGB, nullptr, *image);
    if (FAILED(hr))
        return false;

    if (NeedConvert(image->GetMetadata())) {
        DirectX::ScratchImage* tmp = new DirectX::ScratchImage();
        hr = DirectX::Decompress(*GetImage(image), DXGI_FORMAT_B8G8R8A8_UNORM, *tmp);
        std::swap(tmp, image);
        delete tmp;
        if (FAILED(hr))
            return false;
    }
	
	UpdateSetting(image->GetMetadata());	
	data = image->GetPixels();

	return true;
}

void DDSTexture::UpdateSetting(const DirectX::TexMetadata& meta)
{
	height = meta.height;
	width = meta.width;
	depth = meta.depth;
	array_size = meta.arraySize;
	mip_level = meta.mipLevels;

	auto tex_format = meta.format;
	switch (tex_format)
	{
    case DXGI_FORMAT_R32G32B32A32_TYPELESS:
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
    case DXGI_FORMAT_R32G32B32A32_UINT:
    case DXGI_FORMAT_R32G32B32A32_SINT:           bpc = 32; channel = 4;  break;
    case DXGI_FORMAT_R32G32B32_TYPELESS:          
    case DXGI_FORMAT_R32G32B32_FLOAT:             
    case DXGI_FORMAT_R32G32B32_UINT:              
    case DXGI_FORMAT_R32G32B32_SINT:              bpc = 32; channel = 4;  break;
    case DXGI_FORMAT_R16G16B16A16_TYPELESS:       
    case DXGI_FORMAT_R16G16B16A16_FLOAT:          
    case DXGI_FORMAT_R16G16B16A16_UNORM:          
    case DXGI_FORMAT_R16G16B16A16_UINT:           
    case DXGI_FORMAT_R16G16B16A16_SNORM:          
    case DXGI_FORMAT_R16G16B16A16_SINT:           bpc = 16; channel = 4;  break;
    case DXGI_FORMAT_R32G32_TYPELESS:             
    case DXGI_FORMAT_R32G32_FLOAT:                
    case DXGI_FORMAT_R32G32_UINT:                 
    case DXGI_FORMAT_R32G32_SINT:                 bpc = 32; channel = 2;  break;
    case DXGI_FORMAT_R32G8X24_TYPELESS:
    case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
    case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
    case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:    
    case DXGI_FORMAT_R10G10B10A2_TYPELESS:
    case DXGI_FORMAT_R10G10B10A2_UNORM:
    case DXGI_FORMAT_R10G10B10A2_UINT:
    case DXGI_FORMAT_R11G11B10_FLOAT:             break; // don't support
    case DXGI_FORMAT_R8G8B8A8_TYPELESS:
    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_R8G8B8A8_UINT:
    case DXGI_FORMAT_R8G8B8A8_SNORM:
    case DXGI_FORMAT_R8G8B8A8_SINT:               bpc = 8; channel = 4;  break;
    case DXGI_FORMAT_R16G16_TYPELESS:
    case DXGI_FORMAT_R16G16_FLOAT:
    case DXGI_FORMAT_R16G16_UNORM:
    case DXGI_FORMAT_R16G16_UINT:
    case DXGI_FORMAT_R16G16_SNORM:
    case DXGI_FORMAT_R16G16_SINT:                 bpc = 16; channel = 2;  break;
    case DXGI_FORMAT_R32_TYPELESS:
    case DXGI_FORMAT_D32_FLOAT:
    case DXGI_FORMAT_R32_FLOAT:
    case DXGI_FORMAT_R32_UINT:
    case DXGI_FORMAT_R32_SINT:                    bpc = 32; channel = 1;  break;
    case DXGI_FORMAT_R24G8_TYPELESS:
    case DXGI_FORMAT_D24_UNORM_S8_UINT:
    case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
    case DXGI_FORMAT_X24_TYPELESS_G8_UINT:        break;  // not supported
    case DXGI_FORMAT_R8G8_TYPELESS:
    case DXGI_FORMAT_R8G8_UNORM:
    case DXGI_FORMAT_R8G8_UINT:
    case DXGI_FORMAT_R8G8_SNORM:
    case DXGI_FORMAT_R8G8_SINT:                   bpc = 8; channel = 2;  break;
    case DXGI_FORMAT_R16_TYPELESS:
    case DXGI_FORMAT_R16_FLOAT:
    case DXGI_FORMAT_D16_UNORM:
    case DXGI_FORMAT_R16_UNORM:
    case DXGI_FORMAT_R16_UINT:
    case DXGI_FORMAT_R16_SNORM:
    case DXGI_FORMAT_R16_SINT:                    bpc = 16; channel = 1;  break;
    case DXGI_FORMAT_R8_TYPELESS:
    case DXGI_FORMAT_R8_UNORM:
    case DXGI_FORMAT_R8_UINT:
    case DXGI_FORMAT_R8_SNORM:
    case DXGI_FORMAT_R8_SINT:
    case DXGI_FORMAT_A8_UNORM:                    bpc = 8;  channel = 1;  break;
    case DXGI_FORMAT_R1_UNORM:
    case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
    case DXGI_FORMAT_R8G8_B8G8_UNORM:
    case DXGI_FORMAT_G8R8_G8B8_UNORM:             break;  //not supported
    case DXGI_FORMAT_B5G6R5_UNORM:                
    case DXGI_FORMAT_B5G5R5A1_UNORM:              break;  //not supported
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM:              bpc = 8; channel = 4;  break;
    case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:  break;  //not supported
    case DXGI_FORMAT_B8G8R8A8_TYPELESS:
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8X8_TYPELESS:
    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:         bpc = 8; channel = 4;  break;
    case DXGI_FORMAT_BC6H_TYPELESS:
    case DXGI_FORMAT_BC6H_UF16:
    case DXGI_FORMAT_BC6H_SF16:
    case DXGI_FORMAT_BC7_TYPELESS:
    case DXGI_FORMAT_BC7_UNORM:
    case DXGI_FORMAT_BC7_UNORM_SRGB:              break;
	}
}

bool DDSTexture::NeedConvert(const DirectX::TexMetadata& data)
{
    switch (data.format)
    {
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM:             
    case DXGI_FORMAT_B8G8R8A8_TYPELESS:
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8X8_TYPELESS:
    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:        return false;
    }

    return true;
}

const DirectX::Image* DDSTexture::GetImage(DirectX::ScratchImage* image)
{
	int n_image = image->GetImageCount();
	selected_mip_level = std::min<int>(max_extract_mip_level, image->GetMetadata().mipLevels);
	return image->GetImage(selected_mip_level, 0, 0);
}
