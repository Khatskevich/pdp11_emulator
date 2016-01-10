#pragma once
#include "inttypes.h"

#include "Emulator.h"




class OppCodeGenerator {
private:
	int16_t getImageWidth();
	int16_t getImageHeight();
	int16_t getStartImageAddress();
public:
	int16_t *testGenerate();
};