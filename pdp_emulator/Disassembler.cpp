#include "stdafx.h"
#include "Disassembler.h"

unsigned int default(Operation* operation, unsigned int size);

// this array of functions is responsible for 2 operand functions
unsigned int(*opOperationsDoubleOperandGroup[])(Operation *, unsigned int) = {
	/* 00 */	default, // It is not 2 operand command
	/* 01 */	default, // MOV(W) .1SSDD ZN-0
	/* 02 */	default, // CMP(W) .2SSDD ZNCV
	/* 03 */	default, // BIT(W) .3SSDD ZN-0
	/* 04 */	default, // BIC(W) .4SSDD ZN-0
	/* 05 */	default, // BIS(W) .5SSDD ZN-0
	/* 06 */	default, // ADD( ) .6SSDD ZNCV
	/* 07 */	default, // 
	/* 10 */	default, // It is not 2 operand command
	/* 11 */	default, // MOV(B) .1SSDD ZN-0
	/* 12 */	default, // CMP(B) .2SSDD ZNCV
	/* 13 */	default, // BIT(B) .3SSDD ZN-0
	/* 14 */	default, // BIC(B) .4SSDD ZN-0
	/* 15 */	default, // BIS(B) .5SSDD ZN-0
	/* 16 */	default, // SUB( ) .6SSDD ZNCV
	/* 17 */	default  // 
};

// this array of functions is responsible for 2 operand functions
unsigned int(*opOperationsNoDoubleOperandGroup[])(Operation *, unsigned int) = {
	//                       OPCODE    ZNCV
	/* 0000 */	default, 
	// HALT or 
	// WAIT or 
	// RTI or
	// IOT or
	// RESET or
	/* 0001 */	default, // JMP 0001DD ----
	/* 0002 */	default, // RTS 00020R ----
	/* 0003 */	default, // SWAP 0003DD ++00
	/* 0004 */	default, // BR 0004XX ----
	/* 0005 */	default,
	/* 0006 */	default,
	/* 0007 */	default,
	/* 0010 */	default, // BNE 0010XX ----
	/* 0011 */	default,
	/* 0012 */	default,
	/* 0013 */	default,
	/* 0014 */	default, // BEQ 0014XX -----
	/* 0015 */	default,
	/* 0016 */	default,
	/* 0017 */	default,
	/* 0020 */	default, // BGE 0020XX ----
	/* 0021 */	default,
	/* 0022 */	default,
	/* 0023 */	default,
	/* 0024 */	default, // BLT 0024XX ----
	/* 0025 */	default,
	/* 0026 */	default,
	/* 0027 */	default,
	/* 0030 */	default, // BGT 0030XX -----
	/* 0031 */	default,
	/* 0032 */	default,
	/* 0033 */	default,
	/* 0034 */	default,
	/* 0035 */	default,
	/* 0036 */	default,
	/* 0037 */	default,
	/* 0040 */	default, // JSR 004RDD -----
	/* 0041 */	default, // JSR
	/* 0042 */	default, // JSR
	/* 0043 */	default, // JSR
	/* 0044 */	default, // JSR
	/* 0045 */	default, // JSR
	/* 0046 */	default, // JSR
	/* 0047 */	default, // JSR
	/* 0050 */	default, // CLR(W) .050DD 1000
	/* 0051 */	default, // COM(W) .051DD ++00
	/* 0052 */	default, // INC(W)
	/* 0053 */	default, // DEC(W)
	/* 0054 */	default, // NEG(W)
	/* 0055 */	default, // ADC(W)
	/* 0056 */	default, // SBC(W)
	/* 0057 */	default, // TST(W)
	/* 0060 */	default, // ROR(W)
	/* 0061 */	default, // ROL(W)
	/* 0062 */	default, // ASR(W)
	/* 0063 */	default, // ASL(W)
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
	/* 1000 */	default, // BPL 1000XX ----
	/* 1001 */	default,
	/* 1002 */	default,
	/* 1003 */	default,
	/* 1004 */	default, // BMI 1004XX ----
	/* 1005 */	default,
	/* 1006 */	default,
	/* 1007 */	default,
	/* 1010 */	default, // BHI 1010XX ---
	/* 1011 */	default,
	/* 1012 */	default,
	/* 1013 */	default,
	/* 1014 */	default, // BLOS 1014XX ----
	/* 1015 */	default,
	/* 1016 */	default,
	/* 1017 */	default,
	/* 1020 */	default, // BVC 1020XX ----
	/* 1021 */	default,
	/* 1022 */	default,
	/* 1023 */	default,
	/* 1024 */	default, // BVC 1024XX ---
	/* 1025 */	default,
	/* 1026 */	default,
	/* 1027 */	default,
	/* 1030 */	default, // BCC(BHIS) 1030XX ----
	/* 1031 */	default,
	/* 1032 */	default,
	/* 1033 */	default,
	/* 1034 */	default, // BCS(BLO) 1034XX ----
	/* 1035 */	default,
	/* 1036 */	default,
	/* 1037 */	default,
	/* 1040 */	default, // EMT
	/* 1041 */	default, // EMT
	/* 1042 */	default, // EMT
	/* 1043 */	default, // EMT
	/* 1044 */	default, // TRAP
	/* 1045 */	default, // TRAP
	/* 1046 */	default, // TRAP
	/* 1047 */	default, // TRAP
	/* 1050 */	default,
	/* 1051 */	default,
	/* 1052 */	default,
	/* 1053 */	default,
	/* 1054 */	default,
	/* 1055 */	default,
	/* 1056 */	default,
	/* 1057 */	default,
	/* 1060 */	default,
	/* 1061 */	default,
	/* 1062 */	default,
	/* 1063 */	default,
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

unsigned int Disassembler::disassemble(char*operation_temp, unsigned int size){
	Operation * operation = (Operation*)operation_temp;
	if (checkIfItIsDoubleOperandCommand(operation)){
		return opOperationsDoubleOperandGroup [ getIndexForDobleOperandCommandInFunctionsArray(operation) ](operation, size / 2);
	}
	else{
		return opOperationsDoubleOperandGroup[getIndexForNoDobleOperandCommandInFunctionsArray(operation)](operation, size / 2);
	}
	return 0;
}



int Disassembler::checkIfItIsDoubleOperandCommand(Operation* operation){
	if (operation->DWORD.opcode){
		return 1;
	}
	return 0;
}

unsigned int default(Operation* operation, unsigned int size){
	cout << "Undefined opOperation is called" << endl;
	return 0;
}


