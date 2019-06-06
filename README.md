# Auto-Alignment Tool

Created by **_Dayton Heywood_** June 6th, 2019 for CeeCam Corporation.

## **REQUIREMENTS**:

	Image Magick
	Hugin

## **SETTINGS**:

Settings file contains 2 paths that must be set.

	ImageMagickLocation 	- An absolute path to your ImageMagick bin.   	Example : C:\Program Files\ImageMagick-7.0.8-Q16
	HuginLocation 		- An absolute path to your Hugin bin.   	Example : C:\Program Files\Hugin\bin

## **HOW TO USE**:

Requires 3 arguments to generate and run the compiled batch file.

	-r {path to reference image folder}
	-i {path to input image folder}
	-o {path to output image folder}

## **EXAMPLE COMMAND**:

	"C:\Programs\AutoConfigurationTool\AutoConfigurationTool.exe" -r "C:\Users\Main\Desktop\ref\" -i "C:\Users\Main\Desktop\in\" -o "C:\Users\Main\Desktop\out\"

## **WARNING**:

This process takes a while to complete. Each chunk processed by the script (9 images) takes approximately a minute. 
While the program is running feel free to read the batch file yourself to confirm your batch file contains what you're expecting. Should the program exit unexpectedly it is highly advised to re-run the program and not use the same script twice as it will likely overwrite existing data and simply take longer to process than it would re-generating a new batch file.

## **OUTPUT**:

All output is tracked in the LogFile. There is extremely minimal command terminal output by default. All log files are generated in a folder tagged Logs that will be found in the same location as your exe.
