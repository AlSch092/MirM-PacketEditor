//alsch092 @ github

#pragma once
#include <vcclr.h>
#include <msclr\marshal_cppstd.h>
#include "Script.hpp"

UINT64 g_MirMBase = 0x140000000; //static address, no ASLR due to file packing/section remapping?

BOOL g_LoggingOutboundTraffic = false;
BOOL g_LoggingInboundTraffic = false;

extern std::queue<PacketWriter*> SendPacketQueue;
extern std::queue<PacketWriter*> RecvPacketQueue;

Tasker* g_Robot = new Tasker(); //our 'botting' instance

extern "C"
{
	UINT64 lpEncryptPacketAddress = g_MirMBase + Offsets::EncryptPacket; //change this into constructor using g_mirmbase
	VOID _EncryptPacketHook();

	UINT64 lpSendPacketReturnAddress = g_MirMBase + Offsets::SendPacket + 5;

	UINT64 lpCreatePacketFunc = (UINT64)PacketHelper::LogSendPacketToQueue;
	VOID HandleOutboundPackets();
	
	UINT64 lpCreateRecvPacketFunc = (UINT64)PacketHelper::LogRecvPacketToQueue;
	VOID HandleInboundPackets();

	UINT64 lpGetGameSocketReturnAddress = g_MirMBase + Offsets::GetGameSocket + 7;
	VOID GetGameSocket();

	UINT64 lpSendPacketAddress = 0;
	UINT64 lpKeyPtrLong = 0; //packets above length 6
	UINT64 lpKeyPtrShort = 0; //for packets below length of 6

	SOCKET lpGameSocket = SOCKET_ERROR;
}

namespace MirMCheat {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: Thread^ OutPacketThread;
	public: Thread^ InPacketThread;

private: System::Windows::Forms::CheckBox^  checkBox_LogSendPacket;
private: System::Windows::Forms::TabControl^  tabControl_Main;
	private: System::Windows::Forms::TabPage^  tabPage_Hacks;
	private: System::Windows::Forms::TabPage^  tabPage_Packets;
	private: System::Windows::Forms::CheckBox^  checkBox_LogRecvPackets;



private: System::Windows::Forms::ListView^  listView_SendPackets;
private: System::Windows::Forms::ColumnHeader^  columnHeader_SendPacketLength;
private: System::Windows::Forms::ColumnHeader^  columnHeader_SendPacketOpcode;
private: System::Windows::Forms::ColumnHeader^  columnHeader_SendPacketBuffer;
private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip_Packets;
private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  clearAllToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  blockOpcodeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  ignoreOpcodeToolStripMenuItem;
private: System::Windows::Forms::Button^  button_Send;
private: System::Windows::Forms::TextBox^  textBox_SendPacket;

	private: System::Windows::Forms::RichTextBox^  richTextBox_PacketPosition;
	private: System::Windows::Forms::RichTextBox^  richTextBox_PositionCounter;
	private: System::Windows::Forms::RichTextBox^  richTextBox_PacketInspector;
	private: System::Windows::Forms::GroupBox^  groupBox16;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  textBox_Unicode;
	private: System::Windows::Forms::TextBox^  textBox_ConvStr;

	private: System::Windows::Forms::TextBox^  textBox_32Float;
	private: System::Windows::Forms::TextBox^  textBox_16Float;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  textBox_8Float;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox_ASCII;
	private: System::Windows::Forms::TextBox^  textBox_64Int;
	private: System::Windows::Forms::TextBox^  textBox_32Int;
	private: System::Windows::Forms::TextBox^  textBox_16Int;
	private: System::Windows::Forms::TextBox^  textBox_8Int;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::CheckBox^  checkBox_FishingHack;

	private: System::Windows::Forms::TabPage^  tabPage_Scripting;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_FishingRepeats;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox_ReduceCPU;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::CheckBox^  checkBox_SpamPacket;
	private: System::Windows::Forms::CheckBox^  checkBox_EchoPacket;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::CheckBox^  checkBox_RepeatScript;
	private: System::Windows::Forms::CheckBox^  checkBox_RandomizingLUAName;
	private: System::Windows::Forms::Button^  button_DownloadLUA;
	private: System::Windows::Forms::Button^  button_LoadLUA;
	private: System::Windows::Forms::Button^  button_SaveLUA;
	private: System::Windows::Forms::Button^  button_RunLUA;
	private: System::Windows::Forms::Button^  button_StopLUA;
	private: System::Windows::Forms::TextBox^  textBox_ScriptText;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::Button^  button_WarpPlayer;
	private: System::Windows::Forms::ComboBox^  comboBox_WarpPlayer;
	private: System::Windows::Forms::ColumnHeader^  columnHeader_Direction;
	private: System::Windows::Forms::CheckBox^  checkBox_LogSendPackets;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  searchToolStripMenuItem;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->tabControl_Main = (gcnew System::Windows::Forms::TabControl());
			this->tabPage_Packets = (gcnew System::Windows::Forms::TabPage());
			this->checkBox_LogSendPackets = (gcnew System::Windows::Forms::CheckBox());
			this->button_Send = (gcnew System::Windows::Forms::Button());
			this->textBox_SendPacket = (gcnew System::Windows::Forms::TextBox());
			this->checkBox_LogRecvPackets = (gcnew System::Windows::Forms::CheckBox());
			this->listView_SendPackets = (gcnew System::Windows::Forms::ListView());
			this->columnHeader_Direction = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_SendPacketLength = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_SendPacketOpcode = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_SendPacketBuffer = (gcnew System::Windows::Forms::ColumnHeader());
			this->contextMenuStrip_Packets = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blockOpcodeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ignoreOpcodeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabPage_Hacks = (gcnew System::Windows::Forms::TabPage());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->button_WarpPlayer = (gcnew System::Windows::Forms::Button());
			this->comboBox_WarpPlayer = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox_SpamPacket = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_EchoPacket = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_ReduceCPU = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown_FishingRepeats = (gcnew System::Windows::Forms::NumericUpDown());
			this->checkBox_FishingHack = (gcnew System::Windows::Forms::CheckBox());
			this->tabPage_Scripting = (gcnew System::Windows::Forms::TabPage());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_RepeatScript = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_RandomizingLUAName = (gcnew System::Windows::Forms::CheckBox());
			this->button_DownloadLUA = (gcnew System::Windows::Forms::Button());
			this->button_LoadLUA = (gcnew System::Windows::Forms::Button());
			this->button_SaveLUA = (gcnew System::Windows::Forms::Button());
			this->button_RunLUA = (gcnew System::Windows::Forms::Button());
			this->button_StopLUA = (gcnew System::Windows::Forms::Button());
			this->textBox_ScriptText = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox_PacketPosition = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox_PositionCounter = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox_PacketInspector = (gcnew System::Windows::Forms::RichTextBox());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox_Unicode = (gcnew System::Windows::Forms::TextBox());
			this->textBox_ConvStr = (gcnew System::Windows::Forms::TextBox());
			this->textBox_32Float = (gcnew System::Windows::Forms::TextBox());
			this->textBox_16Float = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox_8Float = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox_ASCII = (gcnew System::Windows::Forms::TextBox());
			this->textBox_64Int = (gcnew System::Windows::Forms::TextBox());
			this->textBox_32Int = (gcnew System::Windows::Forms::TextBox());
			this->textBox_16Int = (gcnew System::Windows::Forms::TextBox());
			this->textBox_8Int = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->searchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl_Main->SuspendLayout();
			this->tabPage_Packets->SuspendLayout();
			this->contextMenuStrip_Packets->SuspendLayout();
			this->tabPage_Hacks->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FishingRepeats))->BeginInit();
			this->tabPage_Scripting->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox16->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl_Main
			// 
			this->tabControl_Main->Controls->Add(this->tabPage_Packets);
			this->tabControl_Main->Controls->Add(this->tabPage_Hacks);
			this->tabControl_Main->Controls->Add(this->tabPage_Scripting);
			this->tabControl_Main->Location = System::Drawing::Point(12, 12);
			this->tabControl_Main->Name = L"tabControl_Main";
			this->tabControl_Main->SelectedIndex = 0;
			this->tabControl_Main->Size = System::Drawing::Size(654, 475);
			this->tabControl_Main->TabIndex = 0;
			// 
			// tabPage_Packets
			// 
			this->tabPage_Packets->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage_Packets->Controls->Add(this->checkBox_LogSendPackets);
			this->tabPage_Packets->Controls->Add(this->button_Send);
			this->tabPage_Packets->Controls->Add(this->textBox_SendPacket);
			this->tabPage_Packets->Controls->Add(this->checkBox_LogRecvPackets);
			this->tabPage_Packets->Controls->Add(this->listView_SendPackets);
			this->tabPage_Packets->Location = System::Drawing::Point(4, 22);
			this->tabPage_Packets->Name = L"tabPage_Packets";
			this->tabPage_Packets->Padding = System::Windows::Forms::Padding(3);
			this->tabPage_Packets->Size = System::Drawing::Size(646, 449);
			this->tabPage_Packets->TabIndex = 1;
			this->tabPage_Packets->Text = L"Packets";
			// 
			// checkBox_LogSendPackets
			// 
			this->checkBox_LogSendPackets->AutoSize = true;
			this->checkBox_LogSendPackets->Location = System::Drawing::Point(6, 429);
			this->checkBox_LogSendPackets->Name = L"checkBox_LogSendPackets";
			this->checkBox_LogSendPackets->Size = System::Drawing::Size(119, 17);
			this->checkBox_LogSendPackets->TabIndex = 4;
			this->checkBox_LogSendPackets->Text = L"Log SEND Packets";
			this->checkBox_LogSendPackets->UseVisualStyleBackColor = true;
			this->checkBox_LogSendPackets->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_LogSendPackets_CheckedChanged);
			// 
			// button_Send
			// 
			this->button_Send->Location = System::Drawing::Point(588, 420);
			this->button_Send->Name = L"button_Send";
			this->button_Send->Size = System::Drawing::Size(52, 23);
			this->button_Send->TabIndex = 3;
			this->button_Send->Text = L"Send";
			this->button_Send->UseVisualStyleBackColor = true;
			this->button_Send->Click += gcnew System::EventHandler(this, &MainForm::button_Send_Click);
			// 
			// textBox_SendPacket
			// 
			this->textBox_SendPacket->Location = System::Drawing::Point(130, 422);
			this->textBox_SendPacket->Name = L"textBox_SendPacket";
			this->textBox_SendPacket->Size = System::Drawing::Size(452, 20);
			this->textBox_SendPacket->TabIndex = 2;
			this->textBox_SendPacket->Text = L"Enter packet...";
			// 
			// checkBox_LogRecvPackets
			// 
			this->checkBox_LogRecvPackets->AutoSize = true;
			this->checkBox_LogRecvPackets->Location = System::Drawing::Point(6, 409);
			this->checkBox_LogRecvPackets->Name = L"checkBox_LogRecvPackets";
			this->checkBox_LogRecvPackets->Size = System::Drawing::Size(118, 17);
			this->checkBox_LogRecvPackets->TabIndex = 1;
			this->checkBox_LogRecvPackets->Text = L"Log RECV Packets";
			this->checkBox_LogRecvPackets->UseVisualStyleBackColor = true;
			this->checkBox_LogRecvPackets->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_LogRecvPackets_CheckedChanged);
			// 
			// listView_SendPackets
			// 
			this->listView_SendPackets->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnHeader_Direction,
					this->columnHeader_SendPacketLength, this->columnHeader_SendPacketOpcode, this->columnHeader_SendPacketBuffer
			});
			this->listView_SendPackets->ContextMenuStrip = this->contextMenuStrip_Packets;
			this->listView_SendPackets->FullRowSelect = true;
			this->listView_SendPackets->GridLines = true;
			this->listView_SendPackets->Location = System::Drawing::Point(4, 6);
			this->listView_SendPackets->Name = L"listView_SendPackets";
			this->listView_SendPackets->Size = System::Drawing::Size(636, 395);
			this->listView_SendPackets->TabIndex = 0;
			this->listView_SendPackets->UseCompatibleStateImageBehavior = false;
			this->listView_SendPackets->View = System::Windows::Forms::View::Details;
			this->listView_SendPackets->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listView_SendPackets_SelectedIndexChanged);
			// 
			// columnHeader_Direction
			// 
			this->columnHeader_Direction->Text = L"S/R";
			this->columnHeader_Direction->Width = 39;
			// 
			// columnHeader_SendPacketLength
			// 
			this->columnHeader_SendPacketLength->Text = L"Length";
			this->columnHeader_SendPacketLength->Width = 45;
			// 
			// columnHeader_SendPacketOpcode
			// 
			this->columnHeader_SendPacketOpcode->Text = L"Opcode";
			this->columnHeader_SendPacketOpcode->Width = 52;
			// 
			// columnHeader_SendPacketBuffer
			// 
			this->columnHeader_SendPacketBuffer->Text = L"Data";
			this->columnHeader_SendPacketBuffer->Width = 656;
			// 
			// contextMenuStrip_Packets
			// 
			this->contextMenuStrip_Packets->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->copyToolStripMenuItem,
					this->clearAllToolStripMenuItem, this->blockOpcodeToolStripMenuItem, this->ignoreOpcodeToolStripMenuItem, this->searchToolStripMenuItem
			});
			this->contextMenuStrip_Packets->Name = L"contextMenuStrip_Packets";
			this->contextMenuStrip_Packets->Size = System::Drawing::Size(154, 136);
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->copyToolStripMenuItem->Text = L"Copy";
			this->copyToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::copyToolStripMenuItem_Click);
			// 
			// clearAllToolStripMenuItem
			// 
			this->clearAllToolStripMenuItem->Name = L"clearAllToolStripMenuItem";
			this->clearAllToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->clearAllToolStripMenuItem->Text = L"Clear All";
			this->clearAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::clearAllToolStripMenuItem_Click);
			// 
			// blockOpcodeToolStripMenuItem
			// 
			this->blockOpcodeToolStripMenuItem->Name = L"blockOpcodeToolStripMenuItem";
			this->blockOpcodeToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->blockOpcodeToolStripMenuItem->Text = L"Block Opcode";
			// 
			// ignoreOpcodeToolStripMenuItem
			// 
			this->ignoreOpcodeToolStripMenuItem->Name = L"ignoreOpcodeToolStripMenuItem";
			this->ignoreOpcodeToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->ignoreOpcodeToolStripMenuItem->Text = L"Ignore Opcode";
			// 
			// tabPage_Hacks
			// 
			this->tabPage_Hacks->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage_Hacks->Controls->Add(this->groupBox6);
			this->tabPage_Hacks->Controls->Add(this->groupBox4);
			this->tabPage_Hacks->Controls->Add(this->groupBox3);
			this->tabPage_Hacks->Controls->Add(this->groupBox2);
			this->tabPage_Hacks->Location = System::Drawing::Point(4, 22);
			this->tabPage_Hacks->Name = L"tabPage_Hacks";
			this->tabPage_Hacks->Padding = System::Windows::Forms::Padding(3);
			this->tabPage_Hacks->Size = System::Drawing::Size(646, 449);
			this->tabPage_Hacks->TabIndex = 0;
			this->tabPage_Hacks->Text = L"Hacks";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->button_WarpPlayer);
			this->groupBox6->Controls->Add(this->comboBox_WarpPlayer);
			this->groupBox6->Location = System::Drawing::Point(383, 7);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(173, 84);
			this->groupBox6->TabIndex = 6;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Warp";
			// 
			// button_WarpPlayer
			// 
			this->button_WarpPlayer->Location = System::Drawing::Point(6, 50);
			this->button_WarpPlayer->Name = L"button_WarpPlayer";
			this->button_WarpPlayer->Size = System::Drawing::Size(161, 23);
			this->button_WarpPlayer->TabIndex = 6;
			this->button_WarpPlayer->Text = L"Teleport";
			this->button_WarpPlayer->UseVisualStyleBackColor = true;
			this->button_WarpPlayer->Click += gcnew System::EventHandler(this, &MainForm::button_WarpPlayer_Click);
			// 
			// comboBox_WarpPlayer
			// 
			this->comboBox_WarpPlayer->FormattingEnabled = true;
			this->comboBox_WarpPlayer->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Bicheon", L"Bicheon Field Entrance",
					L"Gingko Valley", L"Bullside Forest", L"Demon Bull Temple 1F", L"Demon Bull Temple 2F", L"Demon Bull Temple 3F"
			});
			this->comboBox_WarpPlayer->Location = System::Drawing::Point(6, 19);
			this->comboBox_WarpPlayer->Name = L"comboBox_WarpPlayer";
			this->comboBox_WarpPlayer->Size = System::Drawing::Size(161, 21);
			this->comboBox_WarpPlayer->TabIndex = 5;
			this->comboBox_WarpPlayer->Text = L"Bicheon";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBox1);
			this->groupBox4->Controls->Add(this->checkBox_SpamPacket);
			this->groupBox4->Controls->Add(this->checkBox_EchoPacket);
			this->groupBox4->Location = System::Drawing::Point(6, 113);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(202, 100);
			this->groupBox4->TabIndex = 4;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Packets";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(10, 65);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 7;
			// 
			// checkBox_SpamPacket
			// 
			this->checkBox_SpamPacket->AutoSize = true;
			this->checkBox_SpamPacket->Location = System::Drawing::Point(10, 42);
			this->checkBox_SpamPacket->Name = L"checkBox_SpamPacket";
			this->checkBox_SpamPacket->Size = System::Drawing::Size(95, 17);
			this->checkBox_SpamPacket->TabIndex = 5;
			this->checkBox_SpamPacket->Text = L"Spam Packets";
			this->checkBox_SpamPacket->UseVisualStyleBackColor = true;
			// 
			// checkBox_EchoPacket
			// 
			this->checkBox_EchoPacket->AutoSize = true;
			this->checkBox_EchoPacket->Location = System::Drawing::Point(10, 19);
			this->checkBox_EchoPacket->Name = L"checkBox_EchoPacket";
			this->checkBox_EchoPacket->Size = System::Drawing::Size(93, 17);
			this->checkBox_EchoPacket->TabIndex = 3;
			this->checkBox_EchoPacket->Text = L"Echo Packets";
			this->checkBox_EchoPacket->UseVisualStyleBackColor = true;
			this->checkBox_EchoPacket->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_EchoPacket_CheckedChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->checkBox2);
			this->groupBox3->Controls->Add(this->checkBox_ReduceCPU);
			this->groupBox3->Location = System::Drawing::Point(177, 7);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(200, 100);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Resources";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(6, 48);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(91, 17);
			this->checkBox2->TabIndex = 1;
			this->checkBox2->Text = L"Reduce RAM";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox_ReduceCPU
			// 
			this->checkBox_ReduceCPU->AutoSize = true;
			this->checkBox_ReduceCPU->Location = System::Drawing::Point(6, 24);
			this->checkBox_ReduceCPU->Name = L"checkBox_ReduceCPU";
			this->checkBox_ReduceCPU->Size = System::Drawing::Size(89, 17);
			this->checkBox_ReduceCPU->TabIndex = 0;
			this->checkBox_ReduceCPU->Text = L"Reduce CPU";
			this->checkBox_ReduceCPU->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->numericUpDown_FishingRepeats);
			this->groupBox2->Controls->Add(this->checkBox_FishingHack);
			this->groupBox2->Location = System::Drawing::Point(6, 7);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(165, 73);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"E";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 48);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Repeats";
			// 
			// numericUpDown_FishingRepeats
			// 
			this->numericUpDown_FishingRepeats->Location = System::Drawing::Point(72, 44);
			this->numericUpDown_FishingRepeats->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->numericUpDown_FishingRepeats->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown_FishingRepeats->Name = L"numericUpDown_FishingRepeats";
			this->numericUpDown_FishingRepeats->Size = System::Drawing::Size(84, 20);
			this->numericUpDown_FishingRepeats->TabIndex = 2;
			this->numericUpDown_FishingRepeats->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// checkBox_FishingHack
			// 
			this->checkBox_FishingHack->AutoSize = true;
			this->checkBox_FishingHack->Location = System::Drawing::Point(6, 21);
			this->checkBox_FishingHack->Name = L"checkBox_FishingHack";
			this->checkBox_FishingHack->Size = System::Drawing::Size(45, 17);
			this->checkBox_FishingHack->TabIndex = 0;
			this->checkBox_FishingHack->Text = L"Fish";
			this->checkBox_FishingHack->UseVisualStyleBackColor = true;
			this->checkBox_FishingHack->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_FishingHack_CheckedChanged);
			// 
			// tabPage_Scripting
			// 
			this->tabPage_Scripting->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage_Scripting->Controls->Add(this->groupBox5);
			this->tabPage_Scripting->Controls->Add(this->textBox_ScriptText);
			this->tabPage_Scripting->Location = System::Drawing::Point(4, 22);
			this->tabPage_Scripting->Name = L"tabPage_Scripting";
			this->tabPage_Scripting->Size = System::Drawing::Size(646, 449);
			this->tabPage_Scripting->TabIndex = 2;
			this->tabPage_Scripting->Text = L"Scripting";
			// 
			// groupBox5
			// 
			this->groupBox5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox5->BackColor = System::Drawing::Color::Transparent;
			this->groupBox5->Controls->Add(this->checkBox_RepeatScript);
			this->groupBox5->Controls->Add(this->checkBox_RandomizingLUAName);
			this->groupBox5->Controls->Add(this->button_DownloadLUA);
			this->groupBox5->Controls->Add(this->button_LoadLUA);
			this->groupBox5->Controls->Add(this->button_SaveLUA);
			this->groupBox5->Controls->Add(this->button_RunLUA);
			this->groupBox5->Controls->Add(this->button_StopLUA);
			this->groupBox5->Location = System::Drawing::Point(7, 374);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(632, 72);
			this->groupBox5->TabIndex = 17;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Scripting Menu";
			// 
			// checkBox_RepeatScript
			// 
			this->checkBox_RepeatScript->AutoSize = true;
			this->checkBox_RepeatScript->Location = System::Drawing::Point(545, 19);
			this->checkBox_RepeatScript->Name = L"checkBox_RepeatScript";
			this->checkBox_RepeatScript->Size = System::Drawing::Size(80, 17);
			this->checkBox_RepeatScript->TabIndex = 20;
			this->checkBox_RepeatScript->Text = L"Loop Script";
			this->checkBox_RepeatScript->UseVisualStyleBackColor = true;
			// 
			// checkBox_RandomizingLUAName
			// 
			this->checkBox_RandomizingLUAName->AutoSize = true;
			this->checkBox_RandomizingLUAName->Location = System::Drawing::Point(485, 42);
			this->checkBox_RandomizingLUAName->Name = L"checkBox_RandomizingLUAName";
			this->checkBox_RandomizingLUAName->Size = System::Drawing::Size(140, 17);
			this->checkBox_RandomizingLUAName->TabIndex = 19;
			this->checkBox_RandomizingLUAName->Text = L"Randomize Script Name";
			this->checkBox_RandomizingLUAName->UseVisualStyleBackColor = true;
			// 
			// button_DownloadLUA
			// 
			this->button_DownloadLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_DownloadLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_DownloadLUA.BackgroundImage")));
			this->button_DownloadLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_DownloadLUA->Enabled = false;
			this->button_DownloadLUA->Location = System::Drawing::Point(263, 19);
			this->button_DownloadLUA->Name = L"button_DownloadLUA";
			this->button_DownloadLUA->Size = System::Drawing::Size(52, 47);
			this->button_DownloadLUA->TabIndex = 18;
			this->button_DownloadLUA->UseVisualStyleBackColor = false;
			// 
			// button_LoadLUA
			// 
			this->button_LoadLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_LoadLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_LoadLUA.BackgroundImage")));
			this->button_LoadLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_LoadLUA->Location = System::Drawing::Point(201, 20);
			this->button_LoadLUA->Name = L"button_LoadLUA";
			this->button_LoadLUA->Size = System::Drawing::Size(50, 46);
			this->button_LoadLUA->TabIndex = 17;
			this->button_LoadLUA->UseVisualStyleBackColor = false;
			// 
			// button_SaveLUA
			// 
			this->button_SaveLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_SaveLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_SaveLUA.BackgroundImage")));
			this->button_SaveLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_SaveLUA->Location = System::Drawing::Point(137, 20);
			this->button_SaveLUA->Name = L"button_SaveLUA";
			this->button_SaveLUA->Size = System::Drawing::Size(53, 46);
			this->button_SaveLUA->TabIndex = 16;
			this->button_SaveLUA->UseVisualStyleBackColor = false;
			this->button_SaveLUA->Click += gcnew System::EventHandler(this, &MainForm::button_SaveLUA_Click);
			// 
			// button_RunLUA
			// 
			this->button_RunLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_RunLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_RunLUA.BackgroundImage")));
			this->button_RunLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_RunLUA->Location = System::Drawing::Point(10, 20);
			this->button_RunLUA->Name = L"button_RunLUA";
			this->button_RunLUA->Size = System::Drawing::Size(52, 46);
			this->button_RunLUA->TabIndex = 14;
			this->button_RunLUA->UseVisualStyleBackColor = false;
			this->button_RunLUA->Click += gcnew System::EventHandler(this, &MainForm::button_RunLUA_Click);
			// 
			// button_StopLUA
			// 
			this->button_StopLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_StopLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_StopLUA.BackgroundImage")));
			this->button_StopLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_StopLUA->Location = System::Drawing::Point(74, 20);
			this->button_StopLUA->Name = L"button_StopLUA";
			this->button_StopLUA->Size = System::Drawing::Size(50, 46);
			this->button_StopLUA->TabIndex = 15;
			this->button_StopLUA->UseVisualStyleBackColor = false;
			this->button_StopLUA->Click += gcnew System::EventHandler(this, &MainForm::button_StopLUA_Click);
			// 
			// textBox_ScriptText
			// 
			this->textBox_ScriptText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_ScriptText->BackColor = System::Drawing::Color::White;
			this->textBox_ScriptText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox_ScriptText->Location = System::Drawing::Point(7, 7);
			this->textBox_ScriptText->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->textBox_ScriptText->Multiline = true;
			this->textBox_ScriptText->Name = L"textBox_ScriptText";
			this->textBox_ScriptText->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox_ScriptText->Size = System::Drawing::Size(632, 360);
			this->textBox_ScriptText->TabIndex = 5;
			this->textBox_ScriptText->Text = L"ScreenHasLabel(\"Stash\")";
			// 
			// richTextBox_PacketPosition
			// 
			this->richTextBox_PacketPosition->AutoWordSelection = true;
			this->richTextBox_PacketPosition->Font = (gcnew System::Drawing::Font(L"NSimSun", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox_PacketPosition->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->richTextBox_PacketPosition->Location = System::Drawing::Point(7, 50);
			this->richTextBox_PacketPosition->Name = L"richTextBox_PacketPosition";
			this->richTextBox_PacketPosition->ReadOnly = true;
			this->richTextBox_PacketPosition->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->richTextBox_PacketPosition->Size = System::Drawing::Size(66, 290);
			this->richTextBox_PacketPosition->TabIndex = 22;
			this->richTextBox_PacketPosition->Text = resources->GetString(L"richTextBox_PacketPosition.Text");
			this->richTextBox_PacketPosition->WordWrap = false;
			// 
			// richTextBox_PositionCounter
			// 
			this->richTextBox_PositionCounter->Font = (gcnew System::Drawing::Font(L"NSimSun", 9.75F));
			this->richTextBox_PositionCounter->ForeColor = System::Drawing::Color::Red;
			this->richTextBox_PositionCounter->Location = System::Drawing::Point(77, 29);
			this->richTextBox_PositionCounter->Name = L"richTextBox_PositionCounter";
			this->richTextBox_PositionCounter->ReadOnly = true;
			this->richTextBox_PositionCounter->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->richTextBox_PositionCounter->Size = System::Drawing::Size(337, 16);
			this->richTextBox_PositionCounter->TabIndex = 25;
			this->richTextBox_PositionCounter->Text = L"00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n";
			// 
			// richTextBox_PacketInspector
			// 
			this->richTextBox_PacketInspector->Font = (gcnew System::Drawing::Font(L"NSimSun", 9.75F));
			this->richTextBox_PacketInspector->Location = System::Drawing::Point(77, 51);
			this->richTextBox_PacketInspector->Name = L"richTextBox_PacketInspector";
			this->richTextBox_PacketInspector->ReadOnly = true;
			this->richTextBox_PacketInspector->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::ForcedVertical;
			this->richTextBox_PacketInspector->Size = System::Drawing::Size(356, 301);
			this->richTextBox_PacketInspector->TabIndex = 26;
			this->richTextBox_PacketInspector->Text = resources->GetString(L"richTextBox_PacketInspector.Text");
			this->richTextBox_PacketInspector->SelectionChanged += gcnew System::EventHandler(this, &MainForm::richTextBox_PacketInspector_SelectionChanged);
			// 
			// groupBox16
			// 
			this->groupBox16->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox16->Controls->Add(this->label22);
			this->groupBox16->Controls->Add(this->label21);
			this->groupBox16->Controls->Add(this->label20);
			this->groupBox16->Controls->Add(this->label19);
			this->groupBox16->Controls->Add(this->textBox_Unicode);
			this->groupBox16->Controls->Add(this->textBox_ConvStr);
			this->groupBox16->Controls->Add(this->textBox_32Float);
			this->groupBox16->Controls->Add(this->textBox_16Float);
			this->groupBox16->Controls->Add(this->label18);
			this->groupBox16->Controls->Add(this->textBox_8Float);
			this->groupBox16->Controls->Add(this->label17);
			this->groupBox16->Controls->Add(this->label16);
			this->groupBox16->Controls->Add(this->label15);
			this->groupBox16->Controls->Add(this->label14);
			this->groupBox16->Controls->Add(this->label13);
			this->groupBox16->Controls->Add(this->textBox_ASCII);
			this->groupBox16->Controls->Add(this->textBox_64Int);
			this->groupBox16->Controls->Add(this->textBox_32Int);
			this->groupBox16->Controls->Add(this->textBox_16Int);
			this->groupBox16->Controls->Add(this->textBox_8Int);
			this->groupBox16->Font = (gcnew System::Drawing::Font(L"NSimSun", 7.75F));
			this->groupBox16->Location = System::Drawing::Point(6, 358);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(427, 156);
			this->groupBox16->TabIndex = 27;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"Conversion View";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(159, 126);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(47, 11);
			this->label22->TabIndex = 19;
			this->label22->Text = L"Unicode";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(154, 77);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(77, 11);
			this->label21->TabIndex = 18;
			this->label21->Text = L"32-Bit Float";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(156, 99);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(41, 11);
			this->label20->TabIndex = 17;
			this->label20->Text = L"String";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(154, 49);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(77, 11);
			this->label19->TabIndex = 16;
			this->label19->Text = L"16-Bit Float";
			// 
			// textBox_Unicode
			// 
			this->textBox_Unicode->Location = System::Drawing::Point(236, 122);
			this->textBox_Unicode->Name = L"textBox_Unicode";
			this->textBox_Unicode->Size = System::Drawing::Size(70, 19);
			this->textBox_Unicode->TabIndex = 15;
			// 
			// textBox_ConvStr
			// 
			this->textBox_ConvStr->Location = System::Drawing::Point(236, 96);
			this->textBox_ConvStr->Name = L"textBox_ConvStr";
			this->textBox_ConvStr->Size = System::Drawing::Size(172, 19);
			this->textBox_ConvStr->TabIndex = 14;
			// 
			// textBox_32Float
			// 
			this->textBox_32Float->Location = System::Drawing::Point(236, 72);
			this->textBox_32Float->Name = L"textBox_32Float";
			this->textBox_32Float->Size = System::Drawing::Size(70, 19);
			this->textBox_32Float->TabIndex = 13;
			// 
			// textBox_16Float
			// 
			this->textBox_16Float->Location = System::Drawing::Point(237, 46);
			this->textBox_16Float->Name = L"textBox_16Float";
			this->textBox_16Float->Size = System::Drawing::Size(69, 19);
			this->textBox_16Float->TabIndex = 12;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(156, 20);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(71, 11);
			this->label18->TabIndex = 11;
			this->label18->Text = L"8-Bit Float";
			// 
			// textBox_8Float
			// 
			this->textBox_8Float->Font = (gcnew System::Drawing::Font(L"NSimSun", 7.75F));
			this->textBox_8Float->Location = System::Drawing::Point(237, 17);
			this->textBox_8Float->Name = L"textBox_8Float";
			this->textBox_8Float->Size = System::Drawing::Size(69, 19);
			this->textBox_8Float->TabIndex = 10;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(9, 126);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(41, 11);
			this->label17->TabIndex = 9;
			this->label17->Text = L"String";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(9, 97);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(65, 11);
			this->label16->TabIndex = 8;
			this->label16->Text = L"64-Bit Int";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(9, 72);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(65, 11);
			this->label15->TabIndex = 7;
			this->label15->Text = L"32-Bit Int";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(9, 46);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(65, 11);
			this->label14->TabIndex = 6;
			this->label14->Text = L"16-Bit Int";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(9, 20);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(59, 11);
			this->label13->TabIndex = 5;
			this->label13->Text = L"8-Bit Int";
			// 
			// textBox_ASCII
			// 
			this->textBox_ASCII->Location = System::Drawing::Point(83, 123);
			this->textBox_ASCII->Name = L"textBox_ASCII";
			this->textBox_ASCII->Size = System::Drawing::Size(67, 19);
			this->textBox_ASCII->TabIndex = 4;
			// 
			// textBox_64Int
			// 
			this->textBox_64Int->Location = System::Drawing::Point(83, 95);
			this->textBox_64Int->Name = L"textBox_64Int";
			this->textBox_64Int->Size = System::Drawing::Size(67, 19);
			this->textBox_64Int->TabIndex = 3;
			// 
			// textBox_32Int
			// 
			this->textBox_32Int->Location = System::Drawing::Point(83, 69);
			this->textBox_32Int->Name = L"textBox_32Int";
			this->textBox_32Int->Size = System::Drawing::Size(67, 19);
			this->textBox_32Int->TabIndex = 2;
			// 
			// textBox_16Int
			// 
			this->textBox_16Int->Location = System::Drawing::Point(83, 43);
			this->textBox_16Int->Name = L"textBox_16Int";
			this->textBox_16Int->Size = System::Drawing::Size(67, 19);
			this->textBox_16Int->TabIndex = 1;
			// 
			// textBox_8Int
			// 
			this->textBox_8Int->Location = System::Drawing::Point(83, 17);
			this->textBox_8Int->Name = L"textBox_8Int";
			this->textBox_8Int->Size = System::Drawing::Size(67, 19);
			this->textBox_8Int->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->groupBox16);
			this->groupBox1->Controls->Add(this->richTextBox_PacketInspector);
			this->groupBox1->Controls->Add(this->richTextBox_PositionCounter);
			this->groupBox1->Controls->Add(this->richTextBox_PacketPosition);
			this->groupBox1->Location = System::Drawing::Point(668, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(452, 475);
			this->groupBox1->TabIndex = 28;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Inspector";
			// 
			// searchToolStripMenuItem
			// 
			this->searchToolStripMenuItem->Name = L"searchToolStripMenuItem";
			this->searchToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->searchToolStripMenuItem->Text = L"Search";
			this->searchToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::searchToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(1126, 489);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->tabControl_Main);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"MirM Killer";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tabControl_Main->ResumeLayout(false);
			this->tabPage_Packets->ResumeLayout(false);
			this->tabPage_Packets->PerformLayout();
			this->contextMenuStrip_Packets->ResumeLayout(false);
			this->tabPage_Hacks->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FishingRepeats))->EndInit();
			this->tabPage_Scripting->ResumeLayout(false);
			this->tabPage_Scripting->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox16->ResumeLayout(false);
			this->groupBox16->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void ProcessSendQueue() {

	if (SendPacketQueue.size() > 0)
	{
		for (int i = 0; i < SendPacketQueue.size(); i++)
		{
			SendPacketQueue.pop();
		}
	}

	while (g_LoggingOutboundTraffic)
	{
		if (SendPacketQueue.size() > 0)
		{
			PacketWriter* sendPacket = SendPacketQueue.front();

			wchar_t *pwDataText;
			wchar_t pwLengthText[5]; wchar_t pwOpcodeText[10];

			//gets full packet as string
			std::string packetString = PacketHelper::ToString((unsigned char*)sendPacket->GetBuffer(), sendPacket->GetSize());

			DWORD dataSize = sendPacket->GetSize() - 4;
			DWORD dwNum = MultiByteToWideChar(CP_UTF8, 0, packetString.c_str(), -1, NULL, 0);
			_itow_s(dataSize, pwLengthText, 10); //subtract 4 from getSize() to reduce 4 bytes of length in header

			pwDataText = new wchar_t[dwNum];
			MultiByteToWideChar(CP_UTF8, 0, packetString.c_str() + 12, -1, pwDataText, dwNum - 12); //set data text

			if (sendPacket->GetSize() <= 5) //TODO: Clean this code up!
			{
				pwOpcodeText[0] = pwDataText[0]; pwOpcodeText[1] = pwDataText[1]; //Set opcode text
				pwOpcodeText[2] = 0x0000;
			}
			else
			{
				pwOpcodeText[0] = pwDataText[0]; pwOpcodeText[1] = pwDataText[1]; pwOpcodeText[2] = pwDataText[2]; pwOpcodeText[3] = pwDataText[3]; pwOpcodeText[4] = pwDataText[4]; pwOpcodeText[5] = pwDataText[5];
				pwOpcodeText[6] = 0x0000;
			}

			String ^dataString = gcnew String(pwDataText);
			String ^lengthString = gcnew String(pwLengthText);
			String ^OpcodeString = gcnew String(pwOpcodeText);

			cli::array<String^>^ subItems = gcnew cli::array<String^>(4);
			subItems[0] = gcnew String("S");
			subItems[1] = gcnew String(lengthString);
			subItems[2] = gcnew String(OpcodeString);
			subItems[3] = gcnew String(dataString);

			ListViewItem^ itm = gcnew ListViewItem(subItems);
			listView_SendPackets->Items->Add(itm);

			SendPacketQueue.pop();

			delete[] sendPacket->GetBuffer();
			delete sendPacket;
			delete[] pwDataText;

		}
		else	
			Thread::Sleep(300);
	
	}
}

private: System::Void ProcessRecvPacketQueue() {

	if (RecvPacketQueue.size() > 0)
	{
		for (int i = 0; i < RecvPacketQueue.size(); i++)
		{
			RecvPacketQueue.pop();
		}
	}

	while (g_LoggingInboundTraffic)
	{
		if (RecvPacketQueue.size() > 0)
		{
			PacketWriter* recvPacket = RecvPacketQueue.front();

			wchar_t *pwDataText;
			wchar_t pwLengthText[5]; wchar_t pwOpcodeText[10];

			//gets full packet as string
			std::string packetString = PacketHelper::ToString((unsigned char*)recvPacket->GetBuffer(), recvPacket->GetSize());

			DWORD dataSize = recvPacket->GetSize();
			DWORD dwNum = MultiByteToWideChar(CP_UTF8, 0, packetString.c_str(), -1, NULL, 0);
			_itow_s(dataSize, pwLengthText, 10); //

			pwDataText = new wchar_t[dwNum];
			MultiByteToWideChar(CP_UTF8, 0, packetString.c_str(), -1, pwDataText, dwNum); //set data text

			pwOpcodeText[0] = pwDataText[0]; 
			pwOpcodeText[1] = pwDataText[1]; 
			pwOpcodeText[2] = pwDataText[2]; 
			pwOpcodeText[3] = pwDataText[3]; 
			pwOpcodeText[4] = pwDataText[4]; 
			pwOpcodeText[5] = pwDataText[5];
			pwOpcodeText[6] = 0x0000;
			
			String ^dataString = gcnew String(pwDataText);
			String ^lengthString = gcnew String(pwLengthText);
			String ^OpcodeString = gcnew String(pwOpcodeText);

			cli::array<String^>^ subItems = gcnew cli::array<String^>(4);
			subItems[0] = gcnew String("R");
			subItems[1] = gcnew String(lengthString);
			subItems[2] = gcnew String(OpcodeString);
			subItems[3] = gcnew String(dataString);

			ListViewItem^ itm = gcnew ListViewItem(subItems);
			listView_SendPackets->Items->Add(itm);

			RecvPacketQueue.pop();

			delete[] recvPacket->GetBuffer();
			delete recvPacket;
			delete[] pwDataText;

		}
		else
			Thread::Sleep(300);

	}
}

private: System::Void checkBox_LogSendPackets_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	UINT64 HookAddress = g_MirMBase + Offsets::LogSendPacket;

	if (checkBox_LogSendPackets->Checked)
	{
		Hooks::InstallHook((void*)HookAddress, HandleOutboundPackets);
		Hooks::InstallHook((void*)lpEncryptPacketAddress, _EncryptPacketHook);
		Hooks::InstallHook((void*)(lpGetGameSocketReturnAddress - 7), GetGameSocket);

		g_LoggingOutboundTraffic = TRUE;

		OutPacketThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::ProcessSendQueue));
		OutPacketThread->Start();

		printf("Started logging outbond packets!\n");
	}
	else
	{
		Hooks::RemoveHook(HookAddress, 7, (BYTE*)"\x00\x00\x00\x00\x00\x00\x00");
		Hooks::RemoveHook((lpGetGameSocketReturnAddress - 7), 7, (BYTE*)"\x00\x00\x00\x00\x00\x00\x00");
		Hooks::RemoveHook(lpEncryptPacketAddress, 5, (BYTE*)"\x00\x00\x00\x00\x00");

		g_LoggingOutboundTraffic = FALSE;
		printf("Stopped logging outbond packets!\n");

		OutPacketThread->Abort();
	}
}
private: System::Void clearAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	listView_SendPackets->Items->Clear();
}
private: System::Void button_Send_Click(System::Object^  sender, System::EventArgs^  e) {

	if (!lpSendPacketAddress)
	{
		ERR_PRINT("SendPacket address was 0!\n");
		return;
	}

	if (!lpKeyPtrLong )
	{
		ERR_PRINT("lpKeyPtr was 0!\n");
		return;
	}
	else
	{
		printf("KeyPtrs: %llX, %llX\n", lpKeyPtrLong, lpKeyPtrShort);
	}

	String^ Pocket = gcnew String(this->textBox_SendPacket->Text);

	pin_ptr<const wchar_t> wch = PtrToStringChars(Pocket);
	int len = ((Pocket->Length + 1) * 2);
	char* target = new char[len];
	wcstombs(target, wch, len);

	BYTE* Packet = PacketHelper::ToPacketFormat(target); //there could be some problem with this perhaps..

	int length = PacketHelper::GetPacketLength(target);

	PacketBuilder::EncryptAndSend(Packet, length);
	
	free(Packet);
}
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {

	g_MirMBase = (UINT64)GetModuleHandle(NULL);

	if (!g_MirMBase)
	{
		ERR_PRINT("Could not get base address!\n");
		return;
	}

	lpSendPacketAddress = g_MirMBase + Offsets::SendPacket;
	lpGetGameSocketReturnAddress = g_MirMBase + Offsets::GetGameSocket + 7;

	g_Robot->InitializeMapIDs(); //todo: finish filling this out
}

private: System::Void copyPacket()
{
	ListViewItem^ selectedItem;

	for (int i = 0; i < listView_SendPackets->Items->Count; i++)
	{
		selectedItem = listView_SendPackets->Items[i];

		if (selectedItem->Selected == true)
		{
			try
			{
				String^ packetString = selectedItem->SubItems[3]->Text;
				Clipboard::SetDataObject(packetString, true);
			}
			catch (...)
			{
				printf("Could not copy packet, some shit error.\n");
			}
		}
	}
}
private: System::Void copyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::copyPacket));
	newThread->SetApartmentState(System::Threading::ApartmentState::STA);
	newThread->Start();
}

private: void ConvertSelectedData(String^ toConvert) //todo: fix this!
{
	String^ trimmed = toConvert->Replace(" ", "");

	if (trimmed->Length == 0 && toConvert->Length == 0)
		return;

	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(trimmed); //save this code for re-use, great way to convert stuff
	
	string cStr = string();
	cStr = "0x";
	cStr += standardString.c_str();

	if (cStr.size() == 0)
		return;

	uint64_t decimalFromHex = std::stoull(cStr, nullptr, 16);

	uint8_t i8 = (byte)decimalFromHex;
	uint16_t i16 = (uint16_t)PacketHelper::changeEndianness16(decimalFromHex);
	uint32_t i32 = (uint32_t)PacketHelper::changeEndianness32(decimalFromHex);

	try
	{
		textBox_8Int->Text = Convert::ToString(i8); // str_i8;
		textBox_16Int->Text = Convert::ToString(i16);
		textBox_32Int->Text = Convert::ToString(i32);
		textBox_64Int->Text = Convert::ToString(decimalFromHex);

		string strFromHex = PacketHelper::hex_to_string(standardString);
		printf("strFromHex: %s\n", strFromHex.c_str());
		textBox_ConvStr->Text = gcnew String(strFromHex.c_str());
		
	}
	catch (...)
	{
		printf("Conversion failure!\n"); 
	}

	printf("i8: %d\ni32: %d\ni64: %d\n", i8, decimalFromHex, decimalFromHex);

	//free(bytes);
}

private: System::Void richTextBox_PacketInspector_SelectionChanged(System::Object^  sender, System::EventArgs^  e) {

	String^ selected = richTextBox_PacketInspector->SelectedText;
	printf("%s\n", selected);
	ConvertSelectedData(selected);
}
private: System::Void listView_SendPackets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	
	ListViewItem^ selectedItem;

	for (int i = 0; i < listView_SendPackets->Items->Count; i++)
	{
		selectedItem = listView_SendPackets->Items[i];

		if (selectedItem->Selected == true)
		{
			String^ packetString = selectedItem->SubItems[3]->Text;
			richTextBox_PacketInspector->Text = packetString;
		}
	}
}

private: System::Void checkBox_FishingHack_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_FishingHack->Checked) //patched, dont bother
	{
		g_Robot->FishingRepeats = Convert::ToInt32(numericUpDown_FishingRepeats->Value);
		g_Robot->IsFishingExploit = true;
	}
	else
	{
		g_Robot->IsFishingExploit = false;
	}
}
private: System::Void button_RunLUA_Click(System::Object^  sender, System::EventArgs^  e) {
	
	TerminateThread(Scripting::ScriptingThread, 0); //stops any other running thread to make sure none get executed forever and lost

	String^ scriptText = this->textBox_ScriptText->Text;
	g_Robot->ScriptBuffer = (char*)(void*)Marshal::StringToHGlobalAnsi(scriptText);
	printf("ScriptBuffer: %s\n", g_Robot->ScriptBuffer);

	Scripting::ScriptingThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Scripting::ExecuteLUA, 0, 0, 0);
}
private: System::Void button_StopLUA_Click(System::Object^  sender, System::EventArgs^  e) {
	TerminateThread(Scripting::ScriptingThread, 0);
	Scripting::StopLUA(Scripting::L_State);
}

private: void SaveFile()
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();

	saveFileDialog1->Filter = "LUA files (*.lua)|*.lua";
	saveFileDialog1->FilterIndex = 1;
	saveFileDialog1->RestoreDirectory = true;

	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::IO::StreamWriter^ file = gcnew System::IO::StreamWriter(saveFileDialog1->OpenFile());

		// Code to write the stream goes here.
		String^ Script = this->textBox_ScriptText->Text;
		file->Write(Script);
		file->Close();
	}
}

private: System::Void button_SaveLUA_Click(System::Object^  sender, System::EventArgs^  e) {

	Thread^ SaveFileThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::SaveFile));
	SaveFileThread->SetApartmentState(System::Threading::ApartmentState::STA);
	SaveFileThread->Start();
}
private: System::Void checkBox_EchoPacket_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_EchoPacket->Checked)
	{
		g_Robot->EchoPackets = true;
		printf("Activated: Echo packets\n");
	}
	else
	{
		g_Robot->EchoPackets = false;
		printf("Deactivated: Echo packets\n");
	}
}
private: System::Void button_WarpPlayer_Click(System::Object^  sender, System::EventArgs^  e) {

	String^ SelectedMap = comboBox_WarpPlayer->Text;
	char* sMap = (char*)(void*)Marshal::StringToHGlobalAnsi(SelectedMap);

	if (g_Robot->MapIDs.size() == 0)
		g_Robot->InitializeMapIDs();

	if (g_Robot->TeleportToMap(sMap))
	{
		printf("Teleported to: %s\n", sMap);
	}
	else
	{
		printf("Failed to teleport to: %s\n", sMap);
	}

	free(sMap);
}
private: System::Void checkBox_LogRecvPackets_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	UINT64 HookAddress = g_MirMBase + Offsets::OnRecvPacketHook;

	if (checkBox_LogRecvPackets->Checked)
	{
		Hooks::InstallHook((void*)HookAddress, HandleInboundPackets);
		
		g_LoggingInboundTraffic = TRUE;

		InPacketThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::ProcessRecvPacketQueue));
		InPacketThread->Start();

		printf("Started logging RECV packets!\n");
	}
	else
	{
		Hooks::RemoveHook(HookAddress, 5, (BYTE*)"\x00\x00\x00\x00\x00");
		InPacketThread->Abort();
		g_LoggingInboundTraffic = FALSE;
		printf("Stopped logging RECV packets!\n");
	}
}

private: System::Void searchToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	//search packets for pattern

}
};
}
