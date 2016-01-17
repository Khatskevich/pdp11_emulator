#include "stdafx.h"
#include "OppCodeGenerator.h"
#include "Tools.h"
#include <stdlib.h>
#include <cstring>
#include "SimpleDisplay.h"
#define WHITE 0xFFFF
#define BLACK 0x0000

/*
for (y = -heidgt_curr; y<0; y++){
	for (x = -width_curr; x<0; x++){
		*dst = *src;
		dst++;
		src++;
	}
	dst += (height - height_curr)
}
		EXIT

		*/

enum {
	REG,
	//P means pointer or "@"
	REG_P,
	AUTOINC,
	AUTOINC_P,
	AUTODEC,
	AUTODEC_P,
	INDEX,
	INDEX_P
};
#define MOV 1
#define MOVB 9
#define INC 42
#define ADD 6
#define BNE 2
#define BR 1

#define OPERAND(mode, reg) ((((int16_t)mode) << 3) + reg)
#define GENERATE_DOUBLE_OPERANDS_COMMAND(command,ss, dd) oppCodeProgramm[lastPosition++] = ((((int16_t)command) << 12) + (((int16_t)ss << 6) + (dd)))
#define GENERATE_ONE_OPERAND_COMMAND(command, op) oppCodeProgramm[lastPosition++] = ((((int16_t)command) << 6) + (op))
#define GENERATE_BRANCH_COMMAND(command, offset) oppCodeProgramm[lastPosition++] = ((((uint16_t)command) << 8) + ((uint8_t)offset))
#define SET_CONSTANT(constant) oppCodeProgramm[lastPosition++] = constant

#define IMAGE_STARTING_ADDRESS (2*100)
#define BYTE 8

int16_t* OppCodeGenerator::testGenerate(const char *path) {
	int16_t *oppCodeProgramm = (int16_t *)calloc(sizeof(int8_t), MEMORY_SIZE);
	CustomBitmap *bitmap = Tools::readBMP(path);
	int16_t *tmp;
	tmp = setDisplayColor(oppCodeProgramm, WHITE);
	tmp = setDisplayColor(tmp, BLACK);
	generateMovingImageToVideoMemoryProgramm(tmp, bitmap);
	populateImage((int8_t*)oppCodeProgramm + IMAGE_STARTING_ADDRESS, bitmap);
	
	return oppCodeProgramm;
}

void OppCodeGenerator::populateImage(int8_t *oppCodeProgramm, CustomBitmap *bitmap) {
	int indexInBitmap = 0;
	unsigned char* tmp = bitmap->getBuffer();
	
	int x, y;
	int additional_width_per_line = 0;
	int alignment = 0;
	if (bitmap->getWidth() % 8!=0){
		additional_width_per_line = 8 - (bitmap->getWidth() % 8);
	}
	if (bitmap->getWidth() * 3 % 4 != 0){

	}
	for (y = 0; y < bitmap->getHeight(); y++) {
		for ( x = 0; x < bitmap->getWidth(); x++) {
			Tools::setBiteByPosition((int16_t *)oppCodeProgramm, (bitmap->getHeight() - y-1)*(additional_width_per_line + bitmap->getWidth())  + x, Tools::isBlack(tmp[indexInBitmap], tmp[indexInBitmap + 1], tmp[indexInBitmap + 2]));
			indexInBitmap += 3;
			//if (x == bitmap->getWidth() - 1)
			//	indexInBitmap += 4 - (indexInBitmap % 4);
			
	
		}
	}
	bitmap->setWidth(bitmap->getWidth() + additional_width_per_line);
}




int16_t* OppCodeGenerator::generateMovingImageToVideoMemoryProgramm(int16_t *oppCodeProgramm, CustomBitmap *bitmap) {

	/*
	R0 - width / height of display
	R1 - current width
	R2 - current height
	R3 - source addr
	R4 - dst addr
	R5 = R0 - R1
	*/


	/*
	MOV - HEIGHT, R2
	MOV SOURCE_ADDR, R3
	MOV DEST_ADDR, R4
	MOV - R1, R5
	ADD R0, R5
	*/
	int lastPosition = 0;
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R0));
	SET_CONSTANT(DISPLAY_WIDTH / BYTE);
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R2));
	SET_CONSTANT(-bitmap->getHeight());
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R3));
	SET_CONSTANT(IMAGE_STARTING_ADDRESS + ROM_MEMORY);
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R4));
	SET_CONSTANT(VIDEO_MEMORY);
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R1));
	SET_CONSTANT(-bitmap->getWidth() / BYTE);
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R5));
	SET_CONSTANT(DISPLAY_WIDTH / BYTE);
	GENERATE_DOUBLE_OPERANDS_COMMAND(ADD, OPERAND(REG, R1), OPERAND(REG, R5));
	/*
	XLOOP1: MOV -WIDTH, R1
	XLOOP2: MOV (R3)+, (R4)+
	INC R1
	BNE XLOOP2
	ADD R5, R4
	INC R2
	BNE XLOOP1
	*/
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R1));
	SET_CONSTANT(-bitmap->getWidth() / BYTE);

	GENERATE_DOUBLE_OPERANDS_COMMAND(MOVB, OPERAND(AUTOINC, R3), OPERAND(AUTOINC, R4));
	GENERATE_ONE_OPERAND_COMMAND(INC, OPERAND(REG, R1));
	GENERATE_BRANCH_COMMAND(BNE, -2);
	GENERATE_DOUBLE_OPERANDS_COMMAND(ADD, OPERAND(REG, R5), OPERAND(REG, R4));
	GENERATE_ONE_OPERAND_COMMAND(INC, OPERAND(REG, R2));
	GENERATE_BRANCH_COMMAND(BNE, -7);
	//GENERATE_BRANCH_COMMAND(BR, 0);
	return &oppCodeProgramm[lastPosition];
}

int16_t* OppCodeGenerator::setDisplayColor(int16_t *oppCodeProgramm, uint16_t color) {
	/*
		MOV VIDEO_MEMORY R0
		MOV -VIDEO_MEMORY_SIZE R1
		MOV COLOR R2
LOOP:	XOR (R0) (R0)+ //
		INC R1
		BNE LOOP

		*/
	int lastPosition = 0;
	
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R0));
	SET_CONSTANT(VIDEO_MEMORY);
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R1));
	SET_CONSTANT(-VIDEO_MEMORY_SIZE/2);
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R2));
	SET_CONSTANT(color);
	GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(REG, R2), OPERAND(AUTOINC, R0));
	GENERATE_ONE_OPERAND_COMMAND(INC, OPERAND(REG, R1));
	GENERATE_BRANCH_COMMAND(BNE, -2);
	return &(oppCodeProgramm[lastPosition]);
}