#pragma once
#include "inttypes.h"
#include "Emulator.h"
#include "CustomBitmap.h"



class OppCodeGenerator {
private:
	void populateImage(int8_t * buffer, CustomBitmap *bitmap);
	int16_t* generateMovingImageToVideoMemoryProgramm(int16_t *oppCodeProgramm, CustomBitmap *bitmap);
	int16_t* setDisplayColor(int16_t *oppCodeProgramm, uint16_t color);
public:
	int16_t *testGenerate(const char *path);
};