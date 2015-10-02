#include "stdafx.h"
#include "Disassembler.h"

unsigned int default(Operation* operation, unsigned int size);

// this array of functions is responsible for 2 operand functions
unsigned int(*opOperationsDoubleOperandGroup[])(Operation *, unsigned int) = {
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
	/* 17 */	default
};

// this array of functions is responsible for 2 operand functions
unsigned int(*opOperationsNoDoubleOperandGroup[])(Operation *, unsigned int) = {
	/* 0000 */	default,
	/* 0001 */	default,
	/* 0002 */	default,
	/* 0003 */	default,
	/* 0004 */	default,
	/* 0005 */	default,
	/* 0006 */	default,
	/* 0007 */	default,
	/* 0010 */	default,
	/* 0011 */	default,
	/* 0012 */	default,
	/* 0013 */	default,
	/* 0014 */	default,
	/* 0015 */	default,
	/* 0016 */	default,
	/* 0017 */	default,
	/* 0020 */	default,
	/* 0021 */	default,
	/* 0022 */	default,
	/* 0023 */	default,
	/* 0024 */	default,
	/* 0025 */	default,
	/* 0026 */	default,
	/* 0027 */	default,
	/* 0030 */	default,
	/* 0031 */	default,
	/* 0032 */	default,
	/* 0033 */	default,
	/* 0034 */	default,
	/* 0035 */	default,
	/* 0036 */	default,
	/* 0037 */	default,
	/* 0040 */	default,
	/* 0041 */	default,
	/* 0042 */	default,
	/* 0043 */	default,
	/* 0044 */	default,
	/* 0045 */	default,
	/* 0046 */	default,
	/* 0047 */	default,
	/* 0050 */	default,
	/* 0051 */	default,
	/* 0052 */	default,
	/* 0053 */	default,
	/* 0054 */	default,
	/* 0055 */	default,
	/* 0056 */	default,
	/* 0057 */	default,
	/* 0060 */	default,
	/* 0061 */	default,
	/* 0062 */	default,
	/* 0063 */	default,
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
	/* 1000 */	default,
	/* 1001 */	default,
	/* 1002 */	default,
	/* 1003 */	default,
	/* 1004 */	default,
	/* 1005 */	default,
	/* 1006 */	default,
	/* 1007 */	default,
	/* 1010 */	default,
	/* 1011 */	default,
	/* 1012 */	default,
	/* 1013 */	default,
	/* 1014 */	default,
	/* 1015 */	default,
	/* 1016 */	default,
	/* 1017 */	default,
	/* 1020 */	default,
	/* 1021 */	default,
	/* 1022 */	default,
	/* 1023 */	default,
	/* 1024 */	default,
	/* 1025 */	default,
	/* 1026 */	default,
	/* 1027 */	default,
	/* 1030 */	default,
	/* 1031 */	default,
	/* 1032 */	default,
	/* 1033 */	default,
	/* 1034 */	default,
	/* 1035 */	default,
	/* 1036 */	default,
	/* 1037 */	default,
	/* 1040 */	default,
	/* 1041 */	default,
	/* 1042 */	default,
	/* 1043 */	default,
	/* 1044 */	default,
	/* 1045 */	default,
	/* 1046 */	default,
	/* 1047 */	default,
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


