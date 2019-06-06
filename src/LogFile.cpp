#include "HelperPCH.h"

std::ofstream LogFile::LogFileStream;

LogFile::LogFile()
{

}

void LogFile::BeginLogging()
{
	//create our Log folder if it isnt there
	func::DirectoryExists("Logs", true);

	//Create the log file and begin streaming data
	std::string dateFormated = func::CurrentDateTime();
	func::FindAndReplaceAll(dateFormated, ":", ".");
	std::string LogPath = func::GetAbsolutePath("Logs") + "\\" + dateFormated + ".log";
	func::FindAndReplaceAll(LogPath, "\\", "/");

	LogFileStream = std::ofstream(LogPath, std::ios::out);
}

void LogFile::WriteToLog(std::string data)
{
	if (LogFileStream.is_open())
	{
		LogFileStream << func::CurrentDateTime() << " - " << data << std::endl;
	}
}

void LogFile::EndLogging()
{
	if (LogFileStream.is_open())
	{
		LogFileStream.close();
	}
}
