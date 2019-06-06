#pragma once

class LogFile
{
public:
	LogFile();

	static void BeginLogging();

	static void WriteToLog(std::string data);

	static void EndLogging();

private:

	static std::ofstream LogFileStream;
};