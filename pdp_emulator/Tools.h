#pragma once
#include "inttypes.h"
#include "BITMAP.h"
using namespace System::Drawing;
using namespace System;
using namespace System::Drawing::Imaging;

class Tools
{
public:
	static bool getBiteByPosition(uint16_t* buffer, uint16_t position);
	static void setBiteByPosition(uint16_t* buffer, uint16_t position, bool bite);
	static BITMAP* readBMP(char *);
	static bool isBlack(Color color);
	Tools();
};

