#include "HelperPCH.h"

 string Settings::ReferenceImageFolder = "";
 string Settings::OutputImageFolder = "";
 string Settings::InputImageFolder = "";

 string Settings::ImageMagickLocation = "";
 string Settings::HuginLocation = "";

 const unsigned int Settings::TOTAL_SETTINGS;
 string Settings::SETTINGS_HEADERS[TOTAL_SETTINGS] = { IMAGE_MAGICK_HEADER, HUGIN_HEADER };
