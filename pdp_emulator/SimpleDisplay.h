#pragma once

#include "DisassemblerFuncImpl.h"
#include "EmulatorFuncImpl.h"
#include "CustomBitmap.h"
#define DISPLAY_WIDTH 512
#define DISPLAY_HEIGHT 256
#define COLOR_DEPTH 2
#include <list>
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
		void populateFrame();
		void asyncPopulateFrame(void*);
		void swapFrames();
	};