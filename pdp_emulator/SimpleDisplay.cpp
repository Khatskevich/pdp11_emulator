#include "stdafx.h"
#include "SimpleDisplay.h"
#include "Tools.h"


	SimpleDisplay::SimpleDisplay()
	{
	}

	void SimpleDisplay::startDisplaying(){
/*		Bitmap^ image2;
		image2 = gcnew Bitmap(DISPLAY_WIDTH, DISPLAY_HEIGHT, PixelFormat::Format32bppArgb);
		BITMAP *bitmap;
		bitmap = Tools::readBMP("..\\music.bmp");
		unsigned char* tmp = bitmap->getBuffer();
		int x;
		int y;
		unsigned char r, g, b;
		int i = 0;
		for (x = 0; x < DISPLAY_HEIGHT; x++)
		{
			for (y = 0; y < DISPLAY_WIDTH; y++)
			{
			
				//Color newColor = Color::FromArgb(tmp[i], tmp[i+1], tmp[i+2]);
				Color newColor = Tools::isBlack(tmp[i], tmp[i + 1], tmp[i + 2]) ? Color::FromArgb(0, 0, 0) : Color::FromArgb(255, 255, 255);
				image2->SetPixel(y, x, newColor);
				i += 3;
			}
		}
		displayContainer->Image = image2;*/
		populateFrame();
	}

	


	void SimpleDisplay::populateFrame(){
		Bitmap^ image = gcnew Bitmap(DISPLAY_WIDTH, DISPLAY_HEIGHT, PixelFormat::Format32bppArgb);
		int i = 0, x,y;
		for (x = 0; x < DISPLAY_HEIGHT; x++)
		{
			for (y = 0; y < DISPLAY_WIDTH; y++)
			{
				Color newColor = (Tools::getBiteByPosition((int16_t*)videoMemory, i)) ? Color::FromArgb(255, 255, 255) : Color::FromArgb(0, 0, 0);
				image->SetPixel(y, x, newColor);
				i++;
			}
		}
		displayContainer->Image = image;
	};


	void SimpleDisplay::swapFrames(){};

