#include "stdafx.h"
#include "Emulator.h"
#include "EmulatorFuncImpl.h"
#include "stdlib.h"
#include <iostream>
#define _CRT_SECURE_DEPRECATE_MEMORY
#include <memory.h>
#include "inttypes.h"
using namespace std;

uint16_t* getOperand(Operand operand, Emulator * emulator){
	if (operand.split.reg == R_PC){
		uint16_t * result;
		uint16_t * addr;
		uint16_t * A;
		switch (operand.split.mode)
		{
			
		case 2:
			result = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			return result;
		case 3:
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			return (uint16_t*)&emulator->memory[*addr];
		case 6:
			A = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			return (uint16_t*)&emulator->memory[*A + emulator->registers.R[R_PC] ];
		case 7:
			A = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			addr = (uint16_t*)&emulator->memory[*A + emulator->registers.R[R_PC] ];
			return (uint16_t*)&emulator->memory[*addr];
		//default:
			//break;
		}
	}
	else if (operand.split.reg == R_STACK){
		uint16_t * result;
		uint16_t * addr;
		uint16_t * A;
		uint16_t * X;
		switch (operand.split.mode)
		{
		case 0:
			break;
		case 1:
			return &emulator->registers.R[operand.split.reg];
		case 2:
			result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg] += 2; // stack groves to lower adresses
			return result;
		case 3:
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg] += 2;
			return (uint16_t*)&emulator->memory[*addr];
		case 4:
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg] -= 2;
			return (uint16_t*)&emulator->memory[*addr];
		case 5:
			break;
		case 6:
			X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] - *X*2);
			return result;
		case 7:
			X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] - *X*2);
			return (uint16_t*)&emulator->memory[*addr];
		default:
			break;
		}
	}
	else{
		uint16_t * result;
		uint16_t * addr;
		uint16_t * X;
		switch (operand.split.mode)
		{
		case 0:
			return &emulator->registers.R[operand.split.reg];
		case 1:
			return (uint16_t*)(emulator->memory+emulator->registers.R[operand.split.reg]);
		case 2:
			result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg]++;
			return result;
		case 3:
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg]++;
			return (uint16_t*)&emulator->memory[*addr];
		case 4:
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg]+= 2;
			return (uint16_t*)&emulator->memory[*addr];
		case 5:
			emulator->registers.R[operand.split.reg] -= 2;
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			return (uint16_t*)&emulator->memory[*addr];
		case 6:
			X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] + *X);
			emulator->incPc();
			return result;
		case 7:
			X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] + *X);
			emulator->incPc();
			return (uint16_t*)&emulator->memory[*addr];
		default:
			break;
		}
	}
	return 0;
}

#define STANDARD_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W() \
	unsigned int next_command_read = 0;\
	emulator->incPc();\
	Operand operand;\
	operand.raw = 0;\
	operand.split.mode = operation->DWORD.ss;\
	operand.split.reg = operation->DWORD.SS;\
	uint16_t* source = getOperand(operand, emulator);\
	uint16_t source_val = *source; \
	operand.raw = 0;\
	operand.split.mode = operation->DWORD.dd;\
	operand.split.reg = operation->DWORD.DD;\
	uint16_t* destination = getOperand(operand, emulator);\
	uint16_t destination_val = *destination; 

#define SET_DEST_STANDARD_FLAGS_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W() \
		int16_t * dst_temp = (int16_t*)destination; \
		if (!(*dst_temp)) \
		{ 	emulator->registers.flagZ = 1; }\
		else\
		{ emulator->registers.flagZ = 0; };\
		if (*dst_temp < 0)\
		{	emulator->registers.flagN = 1;	}\
		else\
		{ emulator->registers.flagN = 0; }; \
		 emulator->registers.flagV = 0;

void default(Operation* operation, Emulator * emulator){ cout << "Uncnown operation" << oct << operation->raw << endl; emulator->incPc(); };
void MOVW(Operation* operation, Emulator * emulator) { 
	STANDARD_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W()
	*destination = *source;
	SET_DEST_STANDARD_FLAGS_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W()
};
void MOVB(Operation* operation, Emulator * emulator) {
	STANDARD_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W()
		*((char*)destination) = *((char*)source);
};
void CMPW(Operation* operation, Emulator * emulator){
	STANDARD_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W()
		*destination = *source;
};
void CMPB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BITW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BITB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BICW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BICB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BISW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BISB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ADD(Operation* operation, Emulator * emulator) {
	STANDARD_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W()
		*destination += *source;
	SET_DEST_STANDARD_FLAGS_DOUBLE_OPERAND_OPERATION_PERFORMING_PART_W()
};
void SUB(Operation* operation, Emulator * emulator) { default(operation, emulator); };

void HALT_WAIT_RTI_IOT_RESET(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void HALT(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void WAIT(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void RTI(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void IOT(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void RESET(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void JMP(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void RTS(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void SWAP(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BR(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BNE(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BEQ(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BGE(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BLT(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BGT(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void JSR(Operation* operation, Emulator * emulator) { default(operation, emulator); };

void CLRW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void COMW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void INCW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void DECW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void NEGW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ADCW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void SBCW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void TSTW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void RORW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ROLW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ASRW(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ASLW(Operation* operation, Emulator * emulator) { default(operation, emulator); };

void CLRB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void COMB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void INCB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void DECB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void NEGB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ADCB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void SBCB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void TSTB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void RORB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ROLB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ASRB(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void ASLB(Operation* operation, Emulator * emulator) { default(operation, emulator); };

void BPL(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BMI(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BHI(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BLOS(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BVC(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BVS(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BCC(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void BCS(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void EMT(Operation* operation, Emulator * emulator) { default(operation, emulator); };
void TRAP(Operation* operation, Emulator * emulator) { default(operation, emulator); };


