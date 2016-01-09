#include "stdafx.h"
#include "SimpleDisplay.h"
#define WIDTH 64
#define HEIGHT 64
	SimpleDisplay::SimpleDisplay()
	{
	}

	void SimpleDisplay::startDisplaying(){
		Bitmap^ image1;
		Bitmap^ image2;
		image1 = gcnew Bitmap("..\\music.bmp", true);
		image2 = gcnew Bitmap(WIDTH, HEIGHT, PixelFormat::Format32bppArgb);
		unsigned char* tmp = readBMP("..\\music.bmp");
		//memcpy(tmp, videoMemory, WIDTH*HEIGHT * 3);
		int x;
		int y;
		unsigned char r, g, b;
		int i = 0;
		for (x = 0; x < HEIGHT; x++)
		{
			for (y = 0; y < WIDTH; y++)
			{
			

				Color newColor = Color::FromArgb(tmp[i], tmp[i+1], tmp[i+2]);
				image2->SetPixel(x, y, newColor);
				i += 3;
			}
		}
		displayContainer->Image = image2;
	}

	unsigned char* SimpleDisplay::readBMP(char* filename)
	{
		int i;
		FILE* f = fopen(filename, "rb");
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

		// extract image height and width from header
		int width = *(int*)&info[18];
		int height = *(int*)&info[22];

		int size = 3 * width * height;
		unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
		fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
		fclose(f);
		
		for (i = 0; i < size; i += 3)
		{
			unsigned char tmp = data[i];
			data[i] = data[i + 2];
			data[i + 2] = tmp;
		}
		
		return data;
	}