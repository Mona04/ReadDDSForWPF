#pragma once
#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/DDSTextureLoader11.h"
#include <string>

class DDSTexture final
{
public:
	DDSTexture();
	~DDSTexture();

	// if one of width and height is -1, resize using other value with original widht/height ratio.
	// and if all of width and height is -1, a exception is thrown.
	bool LoadTexture(std::wstring_view path, int width = -1, int height = -1);

private:
	void UpdateSetting(const DirectX::TexMetadata& data);
	// return 0 if no process needed, 1 need decompress, 2 need rgba->bgra
	int NeedConvert(const DirectX::TexMetadata& data);
	const DirectX::Image* GetImage(DirectX::ScratchImage* image);

public:
	DXGI_FORMAT format;
	int width = 0;
	int height = 0;
	int depth = 0;
	int channel = 0; // chanel per pixel
	int mem_channel = 0; // even though channel is 3, in memory there can be 4. (cf. DXGI_FORMAT_B8G8R8X8_UNORM)
	int bpc = 0;
	int mip_level = 0;
	uint8_t* data = nullptr;

	int selected_mip_level = 0;
	static int max_extract_mip_level;  // for memory saving set value bigger than 1;

private:
	DirectX::ScratchImage* image = nullptr;
};