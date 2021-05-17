#pragma once
#include <filesystem>
#include <string>

namespace FileSystem {
	std::wstring ToLower(std::wstring_view str);
	std::wstring GetFileNameFromPath(std::wstring_view path);
	std::wstring GetExtension(std::wstring_view path);
	bool IsExistFile(std::wstring_view path);
}