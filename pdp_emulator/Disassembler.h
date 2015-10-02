#pragma once
#include <iostream>
#include "inttypes.h"
using namespace std;

typedef union{
	uint16_t raw;
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

static class Disassembler
{
public:
	Disassembler();
	static string disassemble(char*operation, unsigned int size);
	static int checkIfItIsDoubleOperandCommand(Operation* code);
};

