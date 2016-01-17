#include "stdafx.h"
#include <afxwin.h>
#include "MyForm.h"


UINT updateScreen(void*);

System::Void pdp_emulator::MyForm::button4_Click(System::Object^  sender, System::EventArgs^  e){
	gcroot<SimpleDisplay^>* pointer = new gcroot<SimpleDisplay^>(display);
	AfxBeginThread((AFX_THREADPROC)updateScreen, (LPVOID)pointer);
}


UINT updateScreen(void *pParam)
{
	gcroot<SimpleDisplay^>* pointer = (gcroot<SimpleDisplay^>*)(pParam);
	while (1) {
		Sleep(1000);
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