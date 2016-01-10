#include "stdafx.h"
#include "OppCodeGenerator.h"
#include "Tools.h"
#include <stdlib.h>
#include <cstring>
#include "SimpleDisplay.h"


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

#define OPERAND(mode, reg) ((((int16_t)mode) << 3) + reg)
#define GENERATE_DOUBLE_OPERANDS_COMMAND(command,ss, dd) ((((int16_t)command) << 12) + (((int16_t)ss << 6) + (dd)))
#define GENERATE_ONE_OPERAND_COMMAND(command, op) ((((int16_t)command) << 6) + (op))
#define GENERATE_BRANCH_COMMAND(command, offset) ((((uint16_t)command) << 8) + ((uint8_t)offset))


#define IMAGE_STARTING_ADDRESS 2*25
#define BYTE 8
int16_t* OppCodeGenerator::testGenerate(char *path) {
	int16_t *oppCodeProgramm = (int16_t *)calloc(sizeof(int8_t), MEMORY_SIZE);


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
	BITMAP *bitmap = Tools::readBMP(path);
	oppCodeProgramm[0] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R0));
	oppCodeProgramm[1] = 512 / BYTE;
	oppCodeProgramm[2] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R2));
	oppCodeProgramm[3] = bitmap->getHeight() / BYTE;
	oppCodeProgramm[4] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R3));
	oppCodeProgramm[5] = IMAGE_STARTING_ADDRESS;
	oppCodeProgramm[6] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R4));
	oppCodeProgramm[7] = VIDEO_MEMORY;
	oppCodeProgramm[8] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R1));
	oppCodeProgramm[9] = -bitmap->getWidth() / BYTE;
	oppCodeProgramm[10] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R5));
	oppCodeProgramm[11] = 512 / BYTE;
	oppCodeProgramm[12] = GENERATE_DOUBLE_OPERANDS_COMMAND(ADD, OPERAND(REG, R1), OPERAND(REG, R5));

	
/*
XLOOP1: MOV -WIDTH, R1
XLOOP2: MOV (R3)+, (R4)+
INC R1
BNE XLOOP2
ADD R5, R4
INC R2
BNE XLOOP1
	*/
	oppCodeProgramm[13] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R1));
	oppCodeProgramm[14] = -bitmap->getWidth() / BYTE;

	oppCodeProgramm[15] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOVB, OPERAND(AUTOINC, R3), OPERAND(AUTOINC, R4));
	oppCodeProgramm[16] = GENERATE_ONE_OPERAND_COMMAND(INC, OPERAND(REG, R1));
	oppCodeProgramm[17] = GENERATE_BRANCH_COMMAND(BNE, -2);
	oppCodeProgramm[18] = GENERATE_DOUBLE_OPERANDS_COMMAND(ADD, OPERAND(REG, R5), OPERAND(REG, R4));
	oppCodeProgramm[19] = GENERATE_ONE_OPERAND_COMMAND(INC, OPERAND(REG, R2));
	oppCodeProgramm[20] = GENERATE_BRANCH_COMMAND(BNE, -7); 
	populateImage((int8_t*)oppCodeProgramm + IMAGE_STARTING_ADDRESS, bitmap);
	return oppCodeProgramm;
}

void OppCodeGenerator::populateImage(int8_t *oppCodeProgramm, BITMAP *bitmap) {
	int indexInBitmap = 0;
	unsigned char* tmp = bitmap->getBuffer();
	for (int i = 0; i < bitmap->getHeight() * bitmap->getWidth(); i++) {
		Tools::setBiteByPosition((int16_t *)oppCodeProgramm, i, Tools::isBlack(tmp[indexInBitmap], tmp[indexInBitmap + 1], tmp[indexInBitmap+ 2]));
		indexInBitmap += 3;
	}
}
