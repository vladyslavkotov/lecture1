#ifndef FACTORYCLASSES_H
#define FACTORYCLASSES_H

#include<string>
#include<vector>
#include<fstream>
#include "FileAttrs.h"

class IReportFactory
{
public:
	virtual void WriteReport(const std::vector<FileAttrs>& entries) = 0;
};

class TxtReportFactory : public IReportFactory
{
public:
	static void WriteReport(const std::vector<FileAttrs>& entries);
};

class JsonReportFactory : public IReportFactory
{
public:
	static void WriteReport(const std::vector<FileAttrs>& entries);
};

class CsvReportFactory : public IReportFactory
{
public:
	static void WriteReport(const std::vector<FileAttrs>& entries);
};

#endif
