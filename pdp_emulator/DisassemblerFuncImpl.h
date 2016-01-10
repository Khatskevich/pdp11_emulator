#pragma once
#include "Disassembler.h"
#include "inttypes.h"
#include "Emulator.h"

string default(Operation* operation, unsigned int &size);
string MOVW(Operation* operation, unsigned int &size);
string MOVB(Operation* operation, unsigned int &size);
string CMPW(Operation* operation, unsigned int &size);
string CMPB(Operation* operation, unsigned int &size);
string BITW(Operation* operation, unsigned int &size);
string BITB(Operation* operation, unsigned int &size);
string BICW(Operation* operation, unsigned int &size);
string BICB(Operation* operation, unsigned int &size);
string BISW(Operation* operation, unsigned int &size);
string BISB(Operation* operation, unsigned int &size);
string ADD(Operation* operation, unsigned int &size);
string SUB(Operation* operation, unsigned int &size);

string HALT_WAIT_RTI_IOT_RESET(Operation* operation, unsigned int &size);
string HALT(Operation* operation, unsigned int &size);
string WAIT(Operation* operation, unsigned int &size);
string RTI(Operation* operation, unsigned int &size);
string IOT(Operation* operation, unsigned int &size);
string RESET(Operation* operation, unsigned int &size);
string JMP(Operation* operation, unsigned int &size);
string RTS(Operation* operation, unsigned int &size);
string SWAP(Operation* operation, unsigned int &size);
string BR(Operation* operation, unsigned int &size);
string BNE(Operation* operation, unsigned int &size);
string BEQ(Operation* operation, unsigned int &size);
string BGE(Operation* operation, unsigned int &size);
string BLT(Operation* operation, unsigned int &size);
string BGT(Operation* operation, unsigned int &size);
string JSR(Operation* operation, unsigned int &size);

string CLRW(Operation* operation, unsigned int &size);
string COMW(Operation* operation, unsigned int &size);
string INCW(Operation* operation, unsigned int &size);
string DECW(Operation* operation, unsigned int &size);
string NEGW(Operation* operation, unsigned int &size);
string ADCW(Operation* operation, unsigned int &size);
string SBCW(Operation* operation, unsigned int &size);
string TSTW(Operation* operation, unsigned int &size);
string RORW(Operation* operation, unsigned int &size);
string ROLW(Operation* operation, unsigned int &size);
string ASRW(Operation* operation, unsigned int &size);
string ASLW(Operation* operation, unsigned int &size);

string CLRB(Operation* operation, unsigned int &size);
string COMB(Operation* operation, unsigned int &size);
string INCB(Operation* operation, unsigned int &size);
string DECB(Operation* operation, unsigned int &size);
string NEGB(Operation* operation, unsigned int &size);
string ADCB(Operation* operation, unsigned int &size);
string SBCB(Operation* operation, unsigned int &size);
string TSTB(Operation* operation, unsigned int &size);
string RORB(Operation* operation, unsigned int &size);
string ROLB(Operation* operation, unsigned int &size);
string ASRB(Operation* operation, unsigned int &size);
string ASLB(Operation* operation, unsigned int &size);

string BPL(Operation* operation, unsigned int &size);
string BMI(Operation* operation, unsigned int &size);
string BHI(Operation* operation, unsigned int &size);
string BLOS(Operation* operation, unsigned int &size);
string BVC(Operation* operation, unsigned int &size);
string BVS(Operation* operation, unsigned int &size);
string BCC(Operation* operation, unsigned int &size);
string BCS(Operation* operation, unsigned int &size);
string EMT(Operation* operation, unsigned int &size);
string TRAP(Operation* operation, unsigned int &size);

