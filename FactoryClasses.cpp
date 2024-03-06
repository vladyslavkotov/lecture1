#include "FactoryClasses.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

void CsvReportFactory::WriteReport(const std::vector<FileAttrs>& entries)
{
	std::wofstream csvFile;
	csvFile.open("report.csv");
	csvFile << L"Name,Size,Type,Created,Last Accessed,Last Modified\n";
	for (const FileAttrs& entry : entries)
	{
		csvFile << entry.Name << L"," << entry.Size << L"," << entry.Type << L"," << entry.Created << L"," << entry.Accessed << L"," << entry.Modified << L"\n";
	}
	csvFile.close();
}

void TxtReportFactory::WriteReport(const std::vector<FileAttrs>& entries)
{
	size_t maxNameLength = 0;
	size_t maxSizeLength = 0;

	for (const FileAttrs& entry : entries)
	{
		maxNameLength = entry.Name.length() > maxNameLength ? entry.Name.length() : maxNameLength;
		maxSizeLength = entry.Size.length() > maxSizeLength ? entry.Size.length() : maxSizeLength;
	}
	std::wofstream txtFile;
	txtFile.open("report.txt", std::ios::out | std::ios::app);
	txtFile << L"Name" << std::setw(maxNameLength + maxSizeLength - 1) << "Size" << L"   " << "Type" << L" " << std::setw(22) << "Created" << std::setw(22) << "Accessed" << std::setw(22) << "Modified" << L"\n\n";
	for (const FileAttrs& entry : entries)
	{
		txtFile << entry.Name << std::setw(maxNameLength + maxSizeLength + 3 - entry.Name.length()) << entry.Size << L"   " << entry.Type << std::setw(8 - entry.Type.length()) << L"   " << entry.Created << L"   " << entry.Accessed << L"   " << entry.Modified << L"\n";
	}
	txtFile.close();
}

void JsonReportFactory::WriteReport(const std::vector<FileAttrs>& entries)
{
	std::wofstream jsonFile;
	jsonFile.open("report.json");
	jsonFile << L"{\"Contents\": \n [";
	for (auto i = 0; i < entries.size(); i++)
	{
		const FileAttrs& entry = entries[i];
		jsonFile << L"   \n   {\n";
		jsonFile << L"   \"Name\": \"" << entry.Name << L"\",\n";
		jsonFile << L"   \"Size\": \"" << entry.Size << L"\",\n";
		jsonFile << L"   \"Type\": \"" << entry.Type << L"\",\n";
		jsonFile << L"   \"Created\": \"" << entry.Created << L"\",\n";
		jsonFile << L"   \"LastAccessed\": \"" << entry.Accessed << L"\",\n";
		jsonFile << L"   \"LastModified\": \"" << entry.Modified << L"\"\n";
		jsonFile << L"   }";

		if (i < entries.size() - 1)
		{
			jsonFile << L",";
		}
	}

	jsonFile << L" \n ]\n}\n";
	jsonFile.close();
}