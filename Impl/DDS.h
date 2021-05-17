#pragma once
#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/DDSTextureLoader11.h"
#include <string>

class DDSTexture final
{
public:
	DDSTexture();
	~DDSTexture();

	bool LoadTexture(std::wstring_view path);

private:
	void UpdateSetting(const DirectX::TexMetadata& data);
	bool NeedConvert(const DirectX::TexMetadata& data);
	const DirectX::Image* GetImage(DirectX::ScratchImage* image);

public:
	int width = 0;
	int height = 0;
	int depth = 0;
	int channel = 0; // chanel per pixel
	int bpc = 0;
	int array_size = 0;
	int mip_level = 0;
	uint8_t* data = nullptr;

	int selected_mip_level = 0;

private:
	DirectX::ScratchImage* image = nullptr;

	static int max_extract_mip_level;  // for memory saving set value bigger than 1;
};