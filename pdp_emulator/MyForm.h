#pragma once
#include "DisassemblerFuncImpl.h"
#include "EmulatorFuncImpl.h"
#include "SimpleDisplay.h"
#include "OppCodeGenerator.h"
#include "Disassembler.h"
#include <iomanip>
namespace pdp_emulator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:	Emulator* emulator;
	private:	OppCodeGenerator* oppCodeGenerator;







	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::Button^  button2;







			 SimpleDisplay^ display;
	public:
		template <class T>
string to_string(T t, ios_base & (*f)(ios_base&))
{
  ostringstream oss;
  oss << f << t;
  return oss.str();
}
		MyForm(void)
		{
			InitializeComponent();
			emulator = new Emulator();
			oppCodeGenerator = new OppCodeGenerator();
			display = gcnew SimpleDisplay();
		}

		String^ toHex(uint16_t num) {
			char tmp[20];
			sprintf(tmp, "%X", num);
			String^ tmpString = gcnew String(tmp);
			return tmpString;
		}
		String^ toBin(uint16_t num) {
			char tmp[18];
			for (int i = 15; i >= 8; i--){
				tmp[16-i-1] = (num & (1 << i)) ? '1' : '0';
			}
			tmp[8] = ' ';
			for (int i = 7; i >= 0; i--){
				tmp[16-i] = (num & (1 << i)) ? '1' : '0';
			}
			tmp[17] = '\0';
			return gcnew String(tmp);
		}


		void startSimpleDisplay() {
			//display->setUpSimpleDisplay(this->pictureBox1, (uint8_t *)emulator->getVideoMemory());
			
			showRegisters();
			display->setUpSimpleDisplay(this->pictureBox1, (uint8_t *)emulator->getVideoMemory());
			int16_t* raw = oppCodeGenerator->testGenerate("..\\music.bmp");
			memcpy((void*)emulator->memory, (void*)raw, MEMORY_SIZE);
			display->populateFrame();
			free(raw);
			raw = (int16_t*) emulator->memory;
			int i = 0;
			while ( i < 100) {
				unsigned int size = 0;
				std::string temp = Disassembler::disassemble((char*)(raw + i), size);
				listBox1->Items->Add(toHex(i*2) + "     " + toBin(raw[i]) + "   " + gcnew String(temp.c_str()) );
				i += size+1;
			}
		}
		void step() {
			emulator->step();
			showRegisters();
		}
		void showRegisters(){
			listBox2->Items->Clear();
			for (int i = 0; i < 8; i++){
				listBox2->Items->Add("R" + toHex(i) + " " + toHex(emulator->registers.R[i]));
			}
			listBox2->Items->Add("flagC" + " " + toHex(emulator->registers.flagC));
			listBox2->Items->Add("flagI" + " " + toHex(emulator->registers.flagI));
			listBox2->Items->Add("flagN" + " " + toHex(emulator->registers.flagN));
			listBox2->Items->Add("flagT" + " " + toHex(emulator->registers.flagT));
			listBox2->Items->Add("flagV" + " " + toHex(emulator->registers.flagV));
			listBox2->Items->Add("flagZ" + " " + toHex(emulator->registers.flagZ));
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(141, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Load";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(61, 41);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(258, 187);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(339, 41);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(262, 186);
			this->listBox1->TabIndex = 8;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(339, 233);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(262, 238);
			this->listBox2->TabIndex = 9;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(271, 11);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"step";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(659, 500);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		startSimpleDisplay();
	}
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	step();
}
};
}
