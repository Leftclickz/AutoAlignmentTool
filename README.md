# Auto-Alignment Tool

Created by Dayton Heywood June 6th, 2019 for CeeCam Corporation.
This program is not freely distributable.

## **REQUIREMENTS**:

Image Magick
Hugin

## **SETTINGS**:

Settings file contains 2 paths that must be set.

	ImageMagickLocation - **An absolute** path to your ImageMagick bin.       Example : C:\Program Files\ImageMagick-7.0.8-Q16
	HuginLocation - An **absolute path** to your Hugin bin.  Example : C:\Program Files\Hugin\bin

## **HOW TO USE**:

Requires 3 arguments to generate and run the compiled batch file.

	-r _{path to reference image folder}_
	-i _{path to input image folder}_
	-o _{path to output image folder}_

## **EXAMPLE COMMAND**:

	"C:\Programs\AutoConfigurationTool\AutoConfigurationTool.exe" -r "C:\Users\Main\Desktop\ref\" -i "C:\Users\Main\Desktop\in\" -o "C:\Users\Main\Desktop\out\"

## **WARNING**:

This process takes a while to complete. Each batch processed by the script (9 images) takes approximately a minute. 
While the program is running feel free to read the batch file yourself to confirm your batch file contains what you're expecting.

## **OUTPUT**:

All output is tracking in the LogFile. There is extremely minimal command terminal output.