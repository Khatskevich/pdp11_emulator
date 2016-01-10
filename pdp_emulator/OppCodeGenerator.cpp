#include "stdafx.h"
#include "OppCodeGenerator.h"

#include <stdlib.h>


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
#define INC 42
#define ADD 6
#define BNE 2

#define OPERAND(mode, reg) ((((int16_t)mode) << 3) + reg)
#define GENERATE_DOUBLE_OPERANDS_COMMAND(command,ss, dd) ((((int16_t)command) << 12) + (((int16_t)ss << 6) + (dd)))
#define GENERATE_ONE_OPERAND_COMMAND(command, op) ((((int16_t)command) << 6) + (op))
#define GENERATE_BRANCH_COMMAND(command, offset) ((((int16_t)command) << 8) + (offset))




int16_t* OppCodeGenerator::testGenerate() {
	int16_t *oppCodeProgramm = (int16_t *)calloc(sizeof(int16_t), MEMORY_SIZE);
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
	oppCodeProgramm[0] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R0));
	oppCodeProgramm[1] = 64;
	oppCodeProgramm[2] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R2));
	oppCodeProgramm[3] = 0 - getImageHeight();
	oppCodeProgramm[4] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R3));
	oppCodeProgramm[5] = getStartImageAddress();
	oppCodeProgramm[6] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R4));
	oppCodeProgramm[7] = VIDEO_MEMORY;
	oppCodeProgramm[8] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(REG, R1), OPERAND(REG, R5));
	oppCodeProgramm[9] = GENERATE_DOUBLE_OPERANDS_COMMAND(ADD, OPERAND(REG, R0), OPERAND(REG, R5));


/*
XLOOP : MOV - WIDTH, R1
	MOV(R3) + , (R4)+
	INC R1
	BNE XLOOP
	ADD R5, R4
	INC R2
	BNE XLOOP
*/
	oppCodeProgramm[10] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R1));
	oppCodeProgramm[11] = 0 - getImageWidth();

	oppCodeProgramm[12] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R3), OPERAND(AUTOINC, R4));
	oppCodeProgramm[13] = GENERATE_ONE_OPERAND_COMMAND(INC, OPERAND(REG, R1));
	oppCodeProgramm[14] = GENERATE_BRANCH_COMMAND(BNE, -4);
	oppCodeProgramm[15] = GENERATE_DOUBLE_OPERANDS_COMMAND(ADD, OPERAND(REG, R5), OPERAND(REG, R4));
	oppCodeProgramm[16] = GENERATE_ONE_OPERAND_COMMAND(INC, OPERAND(REG, R2));
	oppCodeProgramm[17] = GENERATE_BRANCH_COMMAND(BNE, -7);

	return oppCodeProgramm;
}


int16_t OppCodeGenerator::getImageWidth() {
	return 0;
}

int16_t OppCodeGenerator::getStartImageAddress() {
	return 0;
}

int16_t OppCodeGenerator::getImageHeight() {
	return 0;
}
