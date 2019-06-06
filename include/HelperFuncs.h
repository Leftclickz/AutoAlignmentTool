#pragma once

#define CURRENT_SETTNG SettingsLoaded[(SettingToLoad - 1)]

namespace func
{
	string CopyFileToString(string filePath);

	bool DirectoryExists(string FolderPath, bool CreateDirectoryIfDoesNotExist);

	string GetAbsolutePath(string relativeFilePath);

	void FindAndReplaceAll(string& data, std::string toSearch, std::string replaceStr);

	const std::string CurrentDateTime();

	bool LoadSettingsFile();

	string GetAFileFromDirectory(string Directory);

	string ExecuteConsoleCommand(string cmd);
}