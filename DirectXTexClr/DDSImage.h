#pragma once
#include "common.h"
#include "../Impl/DDS.h"

ref class DDSImage
{
public:
	DDSImage();
	~DDSImage();

	bool Load(System::String^ path);

private:
	DDSTexture* _impl = nullptr;
};