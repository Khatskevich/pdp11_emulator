#include "stdafx.h"
#include "Tools.h"
#include <stdio.h>


Tools::Tools()
{
}

CustomBitmap* Tools::readBMP(const char* filename)
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
	return new CustomBitmap(height, width, data);
}

bool Tools::getBiteByPosition(int16_t* buffer, int position) {
	int index_of_word = position / 16;
	int index_of_byte = position % 16;
	uint16_t cell = ((uint16_t*)buffer)[index_of_word];
	if (cell & (1 << index_of_byte))
		return true;
	else
		return false;
}

bool Tools::isBlack(int r, int g, int b) { 
	if ((r + g + b) / 3 > 128)
		return true;
	else 
		return false;
}

void Tools::setBiteByPosition(int16_t* buffer, int position, bool bite) {
	int index_of_word = position / 16;
	int index_of_byte = position % 16;
	if (bite) {
		buffer[index_of_word] |= (1 << index_of_byte);
	}
	else {
		buffer[index_of_word] &= ~(1 << index_of_byte);
	}
}