#include "stdafx.h"
#include "Disassembler.h"
#include "DisassemblerFuncImpl.h"

// this array of functions is responsible for 2 operand functions
string (*opOperationsDoubleOperandGroup[])(Operation *, unsigned int) = {
	/* 00 */	default, // It is not 2 operand command
	/* 01 */	MOVW, // MOV(W) .1SSDD ZN-0
	/* 02 */	CMPW, // CMP(W) .2SSDD ZNCV
	/* 03 */	BITW, // BIT(W) .3SSDD ZN-0
	/* 04 */	BICW, // BIC(W) .4SSDD ZN-0
	/* 05 */	BISW, // BIS(W) .5SSDD ZN-0
	/* 06 */	ADD, // ADD( ) .6SSDD ZNCV
	/* 07 */	default, // 
	/* 10 */	default, // It is not 2 operand command
	/* 11 */	MOVB, // MOV(B) .1SSDD ZN-0
	/* 12 */	CMPB, // CMP(B) .2SSDD ZNCV
	/* 13 */	BITB, // BIT(B) .3SSDD ZN-0
	/* 14 */	BICB, // BIC(B) .4SSDD ZN-0
	/* 15 */	BISB, // BIS(B) .5SSDD ZN-0
	/* 16 */	SUB, // SUB( ) .6SSDD ZNCV
	/* 17 */	default  // 
};

// this array of functions is responsible for 2 operand functions
string (*opOperationsNoDoubleOperandGroup[])(Operation *, unsigned int) = {
	//                       OPCODE    ZNCV
	/* 0000 */	HALT_WAIT_RTI_IOT_RESET,
	// HALT or 
	// WAIT or 
	// RTI or
	// IOT or
	// RESET or
	/* 0001 */	JMP, // JMP 0001DD ----
	/* 0002 */	RTS, // RTS 00020R ----
	/* 0003 */	SWAP, // SWAP 0003DD ++00
	/* 0004 */	BR, // BR 0004XX ----
	/* 0005 */	default,
	/* 0006 */	default,
	/* 0007 */	default,
	/* 0010 */	BNE, // BNE 0010XX ----
	/* 0011 */	default,
	/* 0012 */	default,
	/* 0013 */	default,
	/* 0014 */	BEQ, // BEQ 0014XX -----
	/* 0015 */	default,
	/* 0016 */	default,
	/* 0017 */	default,
	/* 0020 */	BGE, // BGE 0020XX ----
	/* 0021 */	default,
	/* 0022 */	default,
	/* 0023 */	default,
	/* 0024 */	BLT, // BLT 0024XX ----
	/* 0025 */	default,
	/* 0026 */	default,
	/* 0027 */	default,
	/* 0030 */	BGT, // BGT 0030XX -----
	/* 0031 */	default,
	/* 0032 */	default,
	/* 0033 */	default,
	/* 0034 */	default,
	/* 0035 */	default,
	/* 0036 */	default,
	/* 0037 */	default,
	/* 0040 */	JSR, // JSR 004RDD -----
	/* 0041 */	JSR, // JSR
	/* 0042 */	JSR, // JSR
	/* 0043 */	JSR, // JSR
	/* 0044 */	JSR, // JSR
	/* 0045 */	JSR, // JSR
	/* 0046 */	JSR, // JSR
	/* 0047 */	JSR, // JSR
	/* 0050 */	CLRW, // CLR(W) .050DD 1000
	/* 0051 */	COMW, // COM(W) .051DD ++00
	/* 0052 */	INCW, // INC(W)
	/* 0053 */	DECW, // DEC(W)
	/* 0054 */	NEGW, // NEG(W)
	/* 0055 */	ADCW, // ADC(W)
	/* 0056 */	SBCW, // SBC(W)
	/* 0057 */	TSTW, // TST(W)
	/* 0060 */	RORW, // ROR(W)
	/* 0061 */	ROLW, // ROL(W)
	/* 0062 */	ASRW, // ASR(W)
	/* 0063 */	ASLW, // ASL(W)
	/* 0064 */	default,
	/* 0065 */	default,
	/* 0066 */	default,
	/* 0067 */	default,
	/* 0070 */	default,
	/* 0071 */	default,
	/* 0072 */	default,
	/* 0073 */	default,
	/* 0074 */	default,
	/* 0075 */	default,
	/* 0076 */	default,
	/* 0077 */	default,
	/* 1000 */	BPL, // BPL 1000XX ----
	/* 1001 */	default,
	/* 1002 */	default,
	/* 1003 */	default,
	/* 1004 */	BMI, // BMI 1004XX ----
	/* 1005 */	default,
	/* 1006 */	default,
	/* 1007 */	default,
	/* 1010 */	BHI, // BHI 1010XX ---
	/* 1011 */	default,
	/* 1012 */	default,
	/* 1013 */	default,
	/* 1014 */	BLOS, // BLOS 1014XX ----
	/* 1015 */	default,
	/* 1016 */	default,
	/* 1017 */	default,
	/* 1020 */	BVC, // BVC 1020XX ----
	/* 1021 */	default,
	/* 1022 */	default,
	/* 1023 */	default,
	/* 1024 */	BVS, // BVC 1024XX ---
	/* 1025 */	default,
	/* 1026 */	default,
	/* 1027 */	default,
	/* 1030 */	BCC, // BCC(BHIS) 1030XX ----
	/* 1031 */	default,
	/* 1032 */	default,
	/* 1033 */	default,
	/* 1034 */	BCS, // BCS(BLO) 1034XX ----
	/* 1035 */	default,
	/* 1036 */	default,
	/* 1037 */	default,
	/* 1040 */	EMT, // EMT
	/* 1041 */	EMT, // EMT
	/* 1042 */	EMT, // EMT
	/* 1043 */	EMT, // EMT
	/* 1044 */	TRAP, // TRAP
	/* 1045 */	TRAP, // TRAP
	/* 1046 */	TRAP, // TRAP
	/* 1047 */	TRAP, // TRAP
	/* 1050 */	CLRB, // CLR(W) .050DD 1000
	/* 1051 */	COMB, // COM(W) .051DD ++00
	/* 1052 */	INCB, // INC(W)
	/* 1053 */	DECB, // DEC(W)
	/* 1054 */	NEGB, // NEG(W)
	/* 1055 */	ADCB, // ADC(W)
	/* 1056 */	SBCB, // SBC(W)
	/* 1057 */	TSTB, // TST(W)
	/* 1060 */	RORB, // ROR(W)
	/* 1061 */	ROLB, // ROL(W)
	/* 1062 */	ASRB, // ASR(W)
	/* 1063 */	ASLB, // ASL(W)
	/* 1064 */	default,
	/* 1065 */	default,
	/* 1066 */	default,
	/* 1067 */	default,
	/* 1070 */	default,
	/* 1071 */	default,
	/* 1072 */	default,
	/* 1073 */	default,
	/* 1074 */	default,
	/* 1075 */	default,
	/* 1076 */	default,
	/* 1077 */	default
};



Disassembler::Disassembler()
{
	Disassembler();
}

unsigned int getIndexForDobleOperandCommandInFunctionsArray(Operation* operation){
	return operation->raw >> 12;
}


unsigned int getIndexForNoDobleOperandCommandInFunctionsArray(Operation* operation){
	return (operation->DWORD.word << 3) + operation->BRANCH.opcode;
}

string Disassembler::disassemble(char*operation_temp, unsigned int size){
	Operation * operation = (Operation*)operation_temp;
	if (checkIfItIsDoubleOperandCommand(operation)){
		return opOperationsDoubleOperandGroup [ getIndexForDobleOperandCommandInFunctionsArray(operation) ](operation, size / 2);
	}
	else{
		return opOperationsDoubleOperandGroup[getIndexForNoDobleOperandCommandInFunctionsArray(operation)](operation, size / 2);
	}
	return NULL;
}



int Disassembler::checkIfItIsDoubleOperandCommand(Operation* operation){
	if (operation->DWORD.opcode){
		return 1;
	}
	return 0;
}




