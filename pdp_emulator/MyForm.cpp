#include "stdafx.h"
#include <afxwin.h>
#include "MyForm.h"


UINT updateScreen(void*);
UINT runEmulator(void *pParam);
System::Void pdp_emulator::MyForm::button4_Click(System::Object^  sender, System::EventArgs^  e){
	emulator->halted = false;
	gcroot<pdp_emulator::MyForm^>* pointer = new gcroot<pdp_emulator::MyForm^>(this);
	AfxBeginThread((AFX_THREADPROC)runEmulator, (LPVOID)pointer);
}


UINT runEmulator (void *pParam)
{
	gcroot<pdp_emulator::MyForm^>* pointer = (gcroot<pdp_emulator::MyForm^>*)(pParam);
	int speed;
	try{
		speed = int::Parse((*pointer)->textBox2->Text);
	}
	catch (...){
		speed = 10;
	}
	do {
		Sleep(speed);
		(*pointer)->getEmulator()->step();
	} while ((*pointer)->getEmulator()->halted == false);
	return 0;
}
System::Void pdp_emulator::MyForm::button1_Click(System::Object^  sender, System::EventArgs^  e) {

	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

	openFileDialog1->InitialDirectory = "..\\";
	openFileDialog1->Filter = "bmp files (*.bmp)|*.bmp";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		emulator->resetRegisters();
		run(openFileDialog1->FileName);
		gcroot<SimpleDisplay^>* pointer = new gcroot<SimpleDisplay^>(display);
		AfxBeginThread((AFX_THREADPROC)updateScreen, (LPVOID)pointer);
	}

}

UINT updateScreen(void *pParam)
{
	gcroot<SimpleDisplay^>* pointer = (gcroot<SimpleDisplay^>*)(pParam);
	while (1) {
		Sleep(100);
		(*pointer)->populateFrame();
	}
	return 0;
}

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	pdp_emulator::MyForm form;
	Application::Run(%form);
}