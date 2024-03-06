#ifndef FILEATTRS_H
#define FILEATTRS_H

#include<string>

struct FileAttrs
{
	std::wstring Name;
	std::wstring Size;
	std::wstring Type;
	std::wstring Created;
	std::wstring Accessed;
	std::wstring Modified;
	FileAttrs(std::wstring name, std::wstring size, std::wstring type, std::wstring created, std::wstring accessed, std::wstring modified);
};

#endif