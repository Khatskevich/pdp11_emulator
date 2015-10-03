#pragma once
#include "inttypes.h"
#define MEMORY_SIZE 65536

typedef union{
	uint32_t raw;
	struct{
		unsigned int mode : 3;
		unsigned int reg : 3;
		unsigned int unused : 26;
	}split;
}Operand;

typedef union{
	uint16_t raw;
	struct{
		unsigned int word : 1;
		unsigned int opcode : 3;
		unsigned int sS : 6;
		unsigned int dD : 6;
	}OPERANDS;
	struct{
		unsigned int word : 1;
		unsigned int opcode : 3;
		unsigned int ss : 3;
		unsigned int SS : 3;
		unsigned int dd : 3;
		unsigned int DD : 3;
	}DWORD;
	struct{
		unsigned int word : 1;
		unsigned int unused : 3;
		unsigned int opcode : 6;
		unsigned int XX : 6;
	}BRANCH;
	struct{
		unsigned int unused : 7;
		unsigned int R : 3;
		unsigned int DD : 6;
	}JSR;
	struct{
		unsigned int unused : 13;
		unsigned int R : 3;
	}RTS;
	struct{
		unsigned int unused : 10;
		unsigned int DD : 6;
	}SINGLE_OPERAND;
}Operation;

#define R_STACK 6
#define R_PC 7

typedef struct{
	uint16_t R[8] ;
	unsigned int flagI ;
	unsigned int flagT ;
	unsigned int flagN ;
	unsigned int flagZ ;
	unsigned int flagV ;
	unsigned int flagC ;
}Registers;

class Emulator
{
public:
	Registers registers;
	char* memory;
	Emulator();
	int writeBufToMemory(char* buf, unsigned int position, unsigned int size );
	int writeByteToMemory(char byte, unsigned int position);
	int writeWordToMemory( uint16_t word, unsigned int position);
	char readByteFromMemory(unsigned int position);
	uint16_t readWordFromMemory(unsigned int position);
	int step();
	void incPc();
};

