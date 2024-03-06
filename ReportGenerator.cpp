#include "ReportGenerator.h"
#include "FileAttrs.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

class FileHandleWrapper
{
	HANDLE hFind;
public:
	FileHandleWrapper(HANDLE handle) : hFind(handle) {}
	~FileHandleWrapper()
	{
		if (hFind != INVALID_HANDLE_VALUE)
		{
			FindClose(hFind);
		}
	}
	HANDLE & GetHandle()
	{
		return hFind;
	}
};

	std::wstring ReportGenerator:: byteSizeToStr(uintmax_t sizeInBytes)
	{
		const std::vector<std::wstring> sizes = { L"B", L"KB", L"MB", L"GB", L"TB" };
		int i = 0;
		double fileSize = static_cast<double>(sizeInBytes);
		while (fileSize >= 1024 && i < sizes.size() - 1)
		{
			fileSize /= 1024;
			i++;
		}
		return std::to_wstring(fileSize) + L" " + std::wstring(sizes[i]);
	}

	std::wstring ReportGenerator:: fileTimeToStr(const FILETIME& fileTime)
	{
		FILETIME localFileTime;
		SYSTEMTIME systemTime;

		FileTimeToLocalFileTime(&fileTime, &localFileTime);
		FileTimeToSystemTime(&localFileTime, &systemTime);

		wchar_t date[32];
		GetDateFormat(LOCALE_USER_DEFAULT, 0, &systemTime, L"yyyy-MM-dd", date, 32);

		wchar_t time[32];
		GetTimeFormat(LOCALE_USER_DEFAULT, 0, &systemTime, L"HH:mm:ss", time, 32);

		return std::wstring(date) + L" " + std::wstring(time);
	}

	uintmax_t ReportGenerator:: getDirectorySize(const std::wstring& directoryPath)
	{
		uintmax_t totalSize = 0;

		for (const auto& file : std::filesystem::recursive_directory_iterator(directoryPath))
		{
			if (file.is_regular_file())
			{
				totalSize += file.file_size();
			}
		}

		return totalSize;
	}

	std::vector<FileAttrs> ReportGenerator:: ListFiles(const std::wstring& directoryPath)
	{
		auto results = std::vector<FileAttrs>();
		WIN32_FIND_DATA data;
		auto hFind = FileHandleWrapper(FindFirstFile((directoryPath + L"\\*").c_str(), &data));
		do
		{
			if (wcscmp(data.cFileName, L".") != 0 && wcscmp(data.cFileName, L"..") != 0)
			{
				if (std::filesystem::is_directory(directoryPath + L"\\" + data.cFileName))
				{
					auto dirSize = byteSizeToStr(getDirectorySize(directoryPath + L"\\" + data.cFileName));
					results.push_back(FileAttrs(
						std::wstring(data.cFileName),
						dirSize,
						L"file",
						fileTimeToStr(data.ftCreationTime),
						fileTimeToStr(data.ftLastAccessTime),
						fileTimeToStr(data.ftLastWriteTime)));
				}
				else
				{
					auto fileSize = byteSizeToStr(std::filesystem::file_size(directoryPath + L"\\" + data.cFileName));
					results.push_back(FileAttrs(
						std::wstring(data.cFileName),
						fileSize,
						L"dir",
						fileTimeToStr(data.ftCreationTime),
						fileTimeToStr(data.ftLastAccessTime),
						fileTimeToStr(data.ftLastWriteTime)));
				}
			}
		} while (FindNextFile(hFind.GetHandle(), &data) != 0);
		return results;
	}

	bool ReportGenerator:: IsValidDirectory(std::wstring& directoryPath)
	{
		bool isValidDirPath = false;
		while (true)
		{
			std::cout << "Enter the directory path: ";
			std::getline(std::wcin, directoryPath);
			auto attributes = GetFileAttributes(directoryPath.c_str());
			if (std::filesystem::is_directory(directoryPath))
			{
				isValidDirPath = true;
				break;
			}
			else if (attributes == INVALID_FILE_ATTRIBUTES || GetLastError() == ERROR_FILE_NOT_FOUND || GetLastError() == ERROR_PATH_NOT_FOUND || directoryPath.size() > (MAX_PATH - 3))
			{
				std::cout << "The path is invalid or the directory does not exist. Please enter a valid path." << "\n";
				continue;
			}
			else
			{
				std::cout << "The path is not a directory. Please enter a valid path." << "\n";
				continue;
			}
		}

		ListFiles(directoryPath);
		return isValidDirPath;
	}

	std::vector<FileAttrs> ReportGenerator:: GenerateReport()
	{
		std::wstring directoryPath;
		if (IsValidDirectory(directoryPath))
		{
			return ListFiles(directoryPath);
		}
	}