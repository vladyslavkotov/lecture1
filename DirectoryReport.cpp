#include "ReportGenerator.h"
#include "FactoryClasses.h"

int main() {
	// path format: C:\my_files
	auto files = ReportGenerator::GenerateReport();
	//JsonReportFactory::WriteReport(files);
	//CsvReportFactory::WriteReport(files);
	TxtReportFactory::WriteReport(files);
	return 0;
}