#include "stdafx.h"
#include "Disassembler.h"

// this array of functions is responsible for 2 operand functions
unsigned int(*opcodesDoubleOperandGroup[])(char *, unsigned int) = {
	/* 00 */	default,
	/* 01 */	default,
	/* 02 */	default,
	/* 03 */	default,
	/* 04 */	default,
	/* 05 */	default,
	/* 06 */	default,
	/* 07 */	default,
	/* 10 */	default,
	/* 11 */	default,
	/* 12 */	default,
	/* 13 */	default,
	/* 14 */	default,
	/* 15 */	default,
	/* 16 */	default,
	/* 17 */	default,
};


Disassembler::Disassembler()
{
	Disassembler();
}


unsigned int Disassembler::disassemble(char*iperation, unsigned int size){
	return 0;
}

unsigned int default(char *code, unsigned int size){
	cout << "Undefined opcode is called" << endl;
	return 0;
}


