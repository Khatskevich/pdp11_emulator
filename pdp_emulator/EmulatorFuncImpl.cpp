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
		switch (operand.split.mode)
		{
		case 2:
			uint16_t * result = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			return result;
		case 3:
			uint16_t * addr = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			return (uint16_t*)&emulator->memory[*addr];
		case 6:
			uint16_t * A = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			return (uint16_t*)&emulator->memory[*A + emulator->registers.R[R_PC] ];
		case 7:
			uint16_t * A = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			emulator->incPc();
			uint16_t *addr = (uint16_t*)&emulator->memory[*A + emulator->registers.R[R_PC] ];
			return (uint16_t*)&emulator->memory[*addr];
		default:
			break;
		}
	}
	else if (operand.split.reg == R_STACK){
		switch (operand.split.mode)
		{
		case 0:
			break;
		case 1:
			return &emulator->registers.R[operand.split.reg];
		case 2:
			uint16_t * result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg] += 2; // stack groves to lower adresses
			return result;
		case 3:
			uint16_t *addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg] += 2;
			return (uint16_t*)&emulator->memory[*addr];
		case 4:
			uint16_t *addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg] -= 2;
			return (uint16_t*)&emulator->memory[*addr];
		case 5:
			break;
		case 6:
			uint16_t * X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			uint16_t * result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] - *X*2);
			return result;
		case 7:
			uint16_t * X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			uint16_t * addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] - *X*2);
			return (uint16_t*)&emulator->memory[*addr];
		default:
			break;
		}
	}
	else{
		switch (operand.split.mode)
		{
		case 0:
			return &emulator->registers.R[operand.split.reg];
		case 1:
			return (uint16_t*)(emulator->memory+emulator->registers.R[operand.split.reg]);
		case 2:
			uint16_t * result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg]++;
			return result;
		case 3:
			uint16_t *addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg]++;
			return (uint16_t*)&emulator->memory[*addr];
		case 4:
			uint16_t *addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			emulator->registers.R[operand.split.reg]+= 2;
			return (uint16_t*)&emulator->memory[*addr];
		case 5:
			emulator->registers.R[operand.split.reg] -= 2;
			uint16_t * addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg]);
			return (uint16_t*)&emulator->memory[*addr];
		case 6:
			uint16_t * X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			uint16_t * result = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] + *X);
			emulator->incPc();
			return result;
		case 7:
			uint16_t * X = (uint16_t*)(emulator->memory + emulator->registers.R[R_PC]);
			uint16_t * addr = (uint16_t*)(emulator->memory + emulator->registers.R[operand.split.reg] + *X);
			emulator->incPc();
			return (uint16_t*)&emulator->memory[*addr];
		default:
			break;
		}
	}
}


void default(Operation* operation, Emulator * emulator);
void MOVW(Operation* operation, Emulator * emulator);
void MOVB(Operation* operation, Emulator * emulator);
void CMPW(Operation* operation, Emulator * emulator);
void CMPB(Operation* operation, Emulator * emulator);
void BITW(Operation* operation, Emulator * emulator);
void BITB(Operation* operation, Emulator * emulator);
void BICW(Operation* operation, Emulator * emulator);
void BICB(Operation* operation, Emulator * emulator);
void BISW(Operation* operation, Emulator * emulator);
void BISB(Operation* operation, Emulator * emulator);
void ADD(Operation* operation, Emulator * emulator);
void SUB(Operation* operation, Emulator * emulator);

void HALT_WAIT_RTI_IOT_RESET(Operation* operation, Emulator * emulator);
void HALT(Operation* operation, Emulator * emulator);
void WAIT(Operation* operation, Emulator * emulator);
void RTI(Operation* operation, Emulator * emulator);
void IOT(Operation* operation, Emulator * emulator);
void RESET(Operation* operation, Emulator * emulator);
void JMP(Operation* operation, Emulator * emulator);
void RTS(Operation* operation, Emulator * emulator);
void SWAP(Operation* operation, Emulator * emulator);
void BR(Operation* operation, Emulator * emulator);
void BNE(Operation* operation, Emulator * emulator);
void BEQ(Operation* operation, Emulator * emulator);
void BGE(Operation* operation, Emulator * emulator);
void BLT(Operation* operation, Emulator * emulator);
void BGT(Operation* operation, Emulator * emulator);
void JSR(Operation* operation, Emulator * emulator);

void CLRW(Operation* operation, Emulator * emulator);
void COMW(Operation* operation, Emulator * emulator);
void INCW(Operation* operation, Emulator * emulator);
void DECW(Operation* operation, Emulator * emulator);
void NEGW(Operation* operation, Emulator * emulator);
void ADCW(Operation* operation, Emulator * emulator);
void SBCW(Operation* operation, Emulator * emulator);
void TSTW(Operation* operation, Emulator * emulator);
void RORW(Operation* operation, Emulator * emulator);
void ROLW(Operation* operation, Emulator * emulator);
void ASRW(Operation* operation, Emulator * emulator);
void ASLW(Operation* operation, Emulator * emulator);

void CLRB(Operation* operation, Emulator * emulator);
void COMB(Operation* operation, Emulator * emulator);
void INCB(Operation* operation, Emulator * emulator);
void DECB(Operation* operation, Emulator * emulator);
void NEGB(Operation* operation, Emulator * emulator);
void ADCB(Operation* operation, Emulator * emulator);
void SBCB(Operation* operation, Emulator * emulator);
void TSTB(Operation* operation, Emulator * emulator);
void RORB(Operation* operation, Emulator * emulator);
void ROLB(Operation* operation, Emulator * emulator);
void ASRB(Operation* operation, Emulator * emulator);
void ASLB(Operation* operation, Emulator * emulator);

void BPL(Operation* operation, Emulator * emulator);
void BMI(Operation* operation, Emulator * emulator);
void BHI(Operation* operation, Emulator * emulator);
void BLOS(Operation* operation, Emulator * emulator);
void BVC(Operation* operation, Emulator * emulator);
void BVS(Operation* operation, Emulator * emulator);
void BCC(Operation* operation, Emulator * emulator);
void BCS(Operation* operation, Emulator * emulator);
void EMT(Operation* operation, Emulator * emulator);
void TRAP(Operation* operation, Emulator * emulator);


