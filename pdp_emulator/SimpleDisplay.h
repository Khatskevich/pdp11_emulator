#pragma once
#include "stdafx.h"
#include "DisassemblerFuncImpl.h"
#include "EmulatorFuncImpl.h"


using namespace System::Drawing;
using namespace System;
using namespace System::Drawing::Imaging;
using namespace System::Windows::Forms;
	public ref class SimpleDisplay
	{
		uint8_t *videoMemory;
		PictureBox ^displayContainer;
	public:
		SimpleDisplay();
		void setUpSimpleDisplay(PictureBox ^pb, uint8_t* vm){
			displayContainer = pb;
			videoMemory = vm;
		};
		void startDisplaying();
		unsigned char* readBMP(char* filename);
	};