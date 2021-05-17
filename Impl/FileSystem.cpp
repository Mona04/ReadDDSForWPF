#include "FileSystem.h"

namespace FileSystem {
	std::wstring ToLower(std::wstring_view str)
	{
		std::wstring result(str);
		for (auto i = result.begin(); i < result.end(); i++)
		{
			if (*i <= L'Z' && *i >= L'A')
				*i = *i - (L'Z' - L'z');
		}
		return result;
	}

	std::wstring GetFileNameFromPath(std::wstring_view path)
	{
		auto lastIndex = path.find_last_of(L"\\/");
		auto fileName = path.substr(lastIndex + 1, path.length());
		
		return std::wstring(fileName);
	}

	std::wstring GetExtension(std::wstring_view path) {
		
		auto fileName = GetFileNameFromPath(path);
		auto lastIndex = fileName.find_last_of(L'.');
		if (lastIndex == std::wstring::npos) return fileName;
		auto extention = fileName.substr(lastIndex + 1, fileName.length());
		
		return ToLower(extention);
	}
	bool IsExistFile(std::wstring_view path)
	{
		try {
			return std::filesystem::exists(path);
		}
		catch (...)
		{
		}
		return false;
	}
}