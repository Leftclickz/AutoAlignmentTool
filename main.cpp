#include "HelperPCH.h"
#include <conio.h>

void ExitProgram();

Timestamp PROGRAM_TIMER;
BatchFile* BATCH_FILE = nullptr;

int main(int argc, char* argv[])
{

	//begin program
	{
		PROGRAM_TIMER.Start();
		LogFile::BeginLogging();
		LogFile::WriteToLog("Initializing Auto-Alignment Tool");
		cout << "Auto-Alignment Tool start. NOTE: check logs for output" << endl;
	}

	//load arguments
	{
		LogFile::WriteToLog("Loading arguments...");
		for (int i = 0; i < argc; i++)
		{
			if (string(argv[i]) == "-r")
			{
				LogFile::WriteToLog("-r argument found. Expecting Reference Folder parameter...");
				if (i + 1 < argc)
				{
					Settings::ReferenceImageFolder = string(argv[i + 1]);
					LogFile::WriteToLog("Reference folder argument found. Using " + Settings::ReferenceImageFolder);
				}
			}
			if (string(argv[i]) == "-i")
			{
				LogFile::WriteToLog("-i argument found. Expecting Input Folder parameter...");
				if (i + 1 < argc)
				{
					Settings::InputImageFolder = string(argv[i + 1]);
					LogFile::WriteToLog("Input folder argument found. Using " + Settings::InputImageFolder);
				}
			}
			if (string(argv[i]) == "-o")
			{
				LogFile::WriteToLog("-o argument found. Expecting Output Folder parameter...");
				if (i + 1 < argc)
				{
					Settings::OutputImageFolder = string(argv[i + 1]);
					LogFile::WriteToLog("Output folder argument found. Using " + Settings::OutputImageFolder);
				}
			}
		}
		if (Settings::ReferenceImageFolder == "" || Settings::InputImageFolder == "" || Settings::OutputImageFolder == "")
		{
			LogFile::WriteToLog("Arguments not valid. Missing parameter.");
			ExitProgram();
		}
		LogFile::WriteToLog("Arguments accepted.");
	}

	//load settings
	{
		LogFile::WriteToLog("Loading settings...");
		if (func::LoadSettingsFile() == false)
			ExitProgram();
	}

	BATCH_FILE = new BatchFile("AutoRun");
	BATCH_FILE->Init(Settings::InputImageFolder, Settings::OutputImageFolder, Settings::ReferenceImageFolder);
	BATCH_FILE->OpenFile();
	BATCH_FILE->GenerateBatchFile();
	BATCH_FILE->RunBatchFile();

	ExitProgram();
}


void ExitProgram()
{
	//end timer
	PROGRAM_TIMER.Stop();

	//display computation time to user
	std::string display = "Program run-time: " + std::to_string(PROGRAM_TIMER.GetElapsedSeconds()) + "s";
	LogFile::WriteToLog(display);

	//Request exit.
	printf("\nPress a key to quit.\n");
	while (!_kbhit())
		fflush(stdout);

	if (BATCH_FILE != nullptr)
	{
		BATCH_FILE->DeleteBatchFile();
		delete BATCH_FILE;
	}

	LogFile::WriteToLog("Program closed successfully.");
	LogFile::EndLogging();

	exit(0);
}
