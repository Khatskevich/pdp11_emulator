#include "stdafx.h"
#include "Tools.h"
#include <stdio.h>

Tools::Tools()
{
}

BITMAP* Tools::readBMP(char* filename)
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
	return new BITMAP(height, width, data);
}

bool Tools::getBiteByPosition(uint16_t* buffer, uint16_t position) {
	int index_of_word = position / sizeof(position);
	int index_of_byte = position % sizeof(position);
	return (buffer[index_of_word] & (1 << index_of_byte));
}

void Tools::setBiteByPosition(uint16_t* buffer, uint16_t position, bool bite) {
	int index_of_word = position / sizeof(position);
	int index_of_byte = position % sizeof(position);
	if (bite) {
		buffer[index_of_word] |= (1 << index_of_byte);
	}
	else {
		buffer[index_of_word] &= ~(1 << index_of_byte);
	}
}