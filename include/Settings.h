#pragma once

#define IMAGE_MAGICK_HEADER "ImageMagickLocation"
#define HUGIN_HEADER "HuginLocation"

using namespace std;

class Settings
{
public:

	static string ReferenceImageFolder;
	static string OutputImageFolder;
	static string InputImageFolder;

	static string ImageMagickLocation;
	static string HuginLocation;

	static const unsigned int TOTAL_SETTINGS = 2;
	static string SETTINGS_HEADERS[TOTAL_SETTINGS];

	enum SH
	{
		DEFAULT,
		IMAGE_MAGICK,
		HUGIN
	};
};