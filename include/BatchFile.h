#pragma once

using namespace std;

//alignment tool def
#define CONVERTED_IMAGE "new0001.tif"
#define ALIGN_EXE "align_image_stack.exe"
#define ALIGN_ARGS(__REF) " -v --corr=0.9 -t 3 --use-given-order -c 100 -s 0 -g 5 -a new " + __REF 
#define CONVERT_CMD(__REF, __NEW) "convert " + __REF + " " + __NEW

class BatchFile
{

public:

	BatchFile(string Name) : m_Name(Name){}
	void Init(string Input, string Output, string Ref);

	void OpenFile();

	void GenerateBatchFile();

	void RunBatchFile();

	void DeleteBatchFile();

protected:

	string m_InputDirectory = "";
	string m_OutputDirectory = "";
	string m_ReferenceDirectory = "";

	string m_Name = "";

	ofstream m_BatchFile;
	bool m_IsGenerated = false;
};