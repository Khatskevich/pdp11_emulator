#pragma once
#include <iostream>
#include "inttypes.h"
#include "Emulator.h"
using namespace std;



static class Disassembler
{
public:
	Disassembler();
	static string disassemble(char*operation, unsigned int &size);
	static int checkIfItIsDoubleOperandCommand(Operation* code);
};

