#pragma once
#include "inttypes.h"
#include "Emulator.h"
#include "BITMAP.h"



class OppCodeGenerator {
private:
	void populateImage(int16_t * buffer, BITMAP *bitmap);
	
public:
	int16_t *testGenerate(char *path);
};