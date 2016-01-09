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
#define MOV 0
#define ADD 6

#define OPERAND(mode, reg) ((((uint16_t)mode) << 3) + reg)
#define GENERATE_DOUBLE_OPERANDS_COMMAND(command,ss, dd) ((((uint16_t)command) << 12) + (((uint16_t)ss << 6) + (dd)))
#define GENERATE_ONE_OPERAND_COMMAND(command,ss, dd) (1)



//WARNING ALL REGISTERS MUST BE SETTED by 0!!!
uint16_t* OppCodeGenerator::testGenerate() {
	uint16_t *oppCodeProgramm = (uint16_t *)calloc(sizeof(uint16_t), MEMORY_SIZE);

	/*
	R0 - width / height of display
	R1 - current width
	R2 - current height
	R3 - source addr
	R4 - dst addr
	R5 = R0 - R1
	*/
	
	//oppCodeProgramm[2] = VIDEO_MEMORY;

	/*
	MOV - HEIGHT, R2
	MOV SOURCE_ADDR, R3
	MOV DEST_ADDR, R4
	MOV - R1, R5
	*/
	oppCodeProgramm[0] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R0));
	oppCodeProgramm[1] = 64;
	//oppCodeProgramm[4] = GENERATE_DOUBLE_OPERANDS_COMMAND(MOV, OPERAND(AUTOINC, R_PC), OPERAND(REG, R4));
	/*
	ADD R0, R5
XLOOP : MOV - WIDTH, R1
		MOV(R3) + , (R4)+
		INC R1
		BNE XLOOP
		ADD R5, R4
		INC R2
		BNE XLOOP
	*/
	return oppCodeProgramm;
}
