#include "HelperPCH.h"

namespace func
{
	std::string CopyFileToString(std::string filePath)
	{
		std::ifstream inputFile(filePath);

		std::string content = "";

		for (int i = 0; inputFile.eof() != true; i++) // get content of infile
			content += inputFile.get();

		content.erase(content.end() - 1);     // erase last character

		inputFile.close();

		return content;
	}

	bool DirectoryExists(std::string FolderPath, bool CreateDirectoryIfDoesNotExist)
	{
		namespace fs = std::experimental::filesystem;
		std::string directoryName = FolderPath;

		if (!fs::is_directory(directoryName) || !fs::exists(directoryName)) // Check if src folder exists
			if (CreateDirectoryIfDoesNotExist)
			{
				fs::create_directory(directoryName); // create src folder
				return true;
			}
			else
				return false;
		else
			return true;
	}

	std::string GetAbsolutePath(std::string relativeFilePath)
	{
		std::string out = std::experimental::filesystem::absolute(std::experimental::filesystem::path(relativeFilePath)).string();
		return out;
	}

	void FindAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr)
	{
		// Get the first occurrence
		size_t pos = data.find(toSearch);

		// Repeat till end is reached
		while (pos != std::string::npos)
		{
			// Replace this occurrence of Sub String
			data.replace(pos, toSearch.size(), replaceStr);
			// Get the next occurrence from the current position
			pos = data.find(toSearch, pos + replaceStr.size());
		}
	}

	const std::string CurrentDateTime()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		std::string data(buf);

		return data;
	}

	bool LoadSettingsFile()
	{
		std::string RawSettingsString = func::CopyFileToString("Settings");
		std::stringstream ss(RawSettingsString);

		bool SettingsLoaded[Settings::TOTAL_SETTINGS] = { false };
		Settings::SH SettingToLoad;

		if (RawSettingsString != "")
		{
			std::string subString;

			//Load all settings
			while (std::getline(ss, subString, '\n'))
			{
				SettingToLoad = Settings::SH::DEFAULT;

				for (unsigned int i = 0; i < Settings::TOTAL_SETTINGS; i++)
					if (subString.find(Settings::SETTINGS_HEADERS[i]) != std::string::npos)
					{
						SettingToLoad = (Settings::SH)(i + 1);
						break;
					}

				if (SettingToLoad == Settings::SH::DEFAULT)
					continue;

				subString = subString.substr(subString.find("=") + 1);
				CURRENT_SETTNG = true;

				switch (SettingToLoad)
				{
				case Settings::IMAGE_MAGICK:
					Settings::ImageMagickLocation = subString;
					break;
				case Settings::HUGIN:
					Settings::HuginLocation = subString;
					break;
				}
			}
		}

		//Did all settings load?
		bool fullyLoaded = true;
		for (unsigned int i = 0; i < Settings::TOTAL_SETTINGS; i++)
			if (SettingsLoaded[i] == false)
			{
				LogFile::WriteToLog("Setting - " + Settings::SETTINGS_HEADERS[i] + " failed to load.");
				fullyLoaded = false;
			}
			else
				LogFile::WriteToLog("Setting - " + Settings::SETTINGS_HEADERS[i] + " loaded successfully.");

		if (fullyLoaded)
			LogFile::WriteToLog("Settings loaded successfully.");
		else
			LogFile::WriteToLog("Settings failed to load.");

		return fullyLoaded;
	}

	string GetAFileFromDirectory(string Directory)
	{
		//get a file
		for (const auto& entry : std::experimental::filesystem::directory_iterator(Directory))
		{
			return func::GetAbsolutePath(entry.path().string());
		}

		return "NO FILE FOUND";
	}

	string ExecuteConsoleCommand(string cmd)
	{
		//add quotes to encapsulate the command into 1 literal in case we're passing args
		std::string quotedCmd = "\"" + cmd + "\"";
		LogFile::WriteToLog("Executing command: " + quotedCmd);

		std::string data;
		FILE * stream;
		const int max_buffer = 256;
		char buffer[max_buffer];
		cmd.append(" 2>&1");

		stream = _popen(quotedCmd.c_str(), "r");
		if (stream) {
			while (!feof(stream))
				if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
			_pclose(stream);
		}

		return data;
	}
}