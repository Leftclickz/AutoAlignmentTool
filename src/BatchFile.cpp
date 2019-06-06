#include "HelperPCH.h"

void BatchFile::Init(string Input, string Output, string Ref)
{
	m_InputDirectory = Input;
	m_OutputDirectory = Output;
	m_ReferenceDirectory = Ref;

	LogFile::WriteToLog("BatchFile " + m_Name + ": initialized.");
}

void BatchFile::OpenFile()
{
	if (m_Name == "")
	{
		LogFile::WriteToLog("BatchFile attempted to open but lacks a Name.");
		return;
	}
	if (m_InputDirectory == "")
	{
		LogFile::WriteToLog("BatchFile attempted to open but lacks an Input Directory.");
		return;
	}
	if (m_OutputDirectory == "")
	{
		LogFile::WriteToLog("BatchFile attempted to open but lacks an Output Directory.");
		return;
	}
	if (m_ReferenceDirectory == "")
	{
		LogFile::WriteToLog("BatchFile attempted to open but lacks a Reference Directory.");
		return;
	}
	if (m_BatchFile.is_open() == true)
	{
		LogFile::WriteToLog("BatchFile attempted to open but is already opened.");
		return;
	}

	m_BatchFile.open(m_Name + ".bat");	
	m_IsGenerated = false;
	LogFile::WriteToLog("BatchFile " + m_Name + ": opened.");
}

void BatchFile::GenerateBatchFile()
{
	if (m_BatchFile.is_open() == false) 
	{
		LogFile::WriteToLog("BatchFile attempted to generate but is not open.");
		return;
	}

	string refImage = "\"" + func::GetAFileFromDirectory(m_ReferenceDirectory) + "\"";
	string alignArgs = ALIGN_ARGS(refImage);
	string alignExe = "\"" + Settings::HuginLocation + "\\" + ALIGN_EXE + "\"";


	//set our working directory
	m_BatchFile << "cd " << "\"" + m_OutputDirectory + "\"" << std::endl;

	//keep track of our original image names
	std::vector<std::string> originalImageNamesVector;

	unsigned int argCount = 0;
	for (const auto& entry : std::experimental::filesystem::directory_iterator(m_InputDirectory))
	{
		std::string imagePath = "\"" + entry.path().string() + "\"";
		std::string imageNameOnly = entry.path().string();

		func::FindAndReplaceAll(imageNameOnly, m_InputDirectory + "\\", "");

		//check to see if we have already aligned this image
		if (std::experimental::filesystem::exists(m_OutputDirectory + "\\" + imageNameOnly))
			continue;
		//if it doesnt exist add it to the argument list
		else
		{
			LogFile::WriteToLog("BatchFile " + m_Name + ": Added image " + imagePath + " to alignment queue.");
			alignArgs += " " + imagePath;
			originalImageNamesVector.push_back(imageNameOnly);
			argCount++;

			//only process 9 args at a time
			if (argCount == 9)
			{
				m_BatchFile << alignExe + alignArgs << std::endl;
				alignArgs = ALIGN_ARGS(refImage);

				for (unsigned int a = 0; a < argCount; a++)
					m_BatchFile << "\"" << Settings::ImageMagickLocation << "\\convert.exe" << "\" " << "new000" + std::to_string(a + 1) + ".tif " << originalImageNamesVector[a] << std::endl;

				m_BatchFile << "del /F/Q " << "\"" + m_OutputDirectory + "\\" + "*.tif" + "\"" << " > NUL" << std::endl;

				originalImageNamesVector.clear();
				argCount = 0;
			}
		}
	}

	//add the remainder
	if (argCount > 0)
	{
		m_BatchFile << alignExe + alignArgs << std::endl;
		for (unsigned int a = 0; a < argCount; a++)
			m_BatchFile << "\"" << Settings::ImageMagickLocation << "\\convert.exe" << "\" " << "new000" + std::to_string(a + 1) + ".tif " << originalImageNamesVector[a] << std::endl;

		m_BatchFile << "del /F/Q " << "\"" + m_OutputDirectory +  "\\" + "*.tif" + "\"" << " > NUL" << std::endl;
		originalImageNamesVector.clear();
	}

	m_BatchFile.close();
	LogFile::WriteToLog("BatchFile " + m_Name + ": generated.");
	m_IsGenerated = true;
}

void BatchFile::RunBatchFile()
{
	if (m_IsGenerated == false)
	{
		LogFile::WriteToLog("BatchFile attempted to run but has not been generated.");
		return;
	}

	string path = func::GetAbsolutePath(m_Name + ".bat");

	LogFile::WriteToLog("BatchFile " + m_Name + ": run command processing.");
	LogFile::WriteToLog("Executing process with command " + path);
	//run a process with our batch file
	//kGUICallThread ProcessHandle;
	//ProcessHandle.Start(path.c_str(), CALLTHREAD_READ);
	//std::string out = *ProcessHandle.GetString();
	string out = func::ExecuteConsoleCommand(path);
	LogFile::WriteToLog("Output: \n" + out);



	LogFile::WriteToLog("BatchFile " + m_Name + ": ran.");
}

void BatchFile::DeleteBatchFile()
{
	if (m_IsGenerated == false)
	{
		LogFile::WriteToLog("BatchFile attempted to delete but has not generated a file to delete.");
		return;
	}

	string path = func::GetAbsolutePath(m_Name + ".bat");
	remove(path.c_str());

	LogFile::WriteToLog("BatchFile " + m_Name + ": deleted.");
}
