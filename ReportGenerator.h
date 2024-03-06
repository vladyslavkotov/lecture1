#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "FileAttrs.h"

#include <windows.h>
#include <string>
#include <vector>


class ReportGenerator
{
	static std::wstring byteSizeToStr(uintmax_t sizeInBytes);

	static std::wstring fileTimeToStr(const FILETIME& fileTime);

	static uintmax_t getDirectorySize(const std::wstring& directoryPath);

	static std::vector<FileAttrs> ListFiles(const std::wstring& directoryPath);

	static bool IsValidDirectory(std::wstring& directoryPath);

	public:
	static std::vector<FileAttrs> GenerateReport();
};

#endif
