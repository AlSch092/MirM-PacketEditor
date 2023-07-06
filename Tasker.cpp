#include "Tasker.hpp"

void Tasker::SpamFishing(Tasker* pThis) //now patched, old exploit
{
	printf("Starting spam fishing...\n");

	for (int i = 0; i < pThis->FishingRepeats; i++)
	{
		PacketWriter* p = Factory::Fishing(pThis->FishingHash, 2, 7);

		if (PacketBuilder::EncryptAndSend((BYTE*)p->GetBuffer(), p->GetSize()) == SOCKET_ERROR)
		{
			printf("[ERROR] Disconnected while auto-fishing!\n");
		}

		delete p->GetBuffer();
		delete p;
	}
}

void Tasker::InitializeMapIDs() //todo: check if these are stored in some packed CSV in the game, this method is not ideal for scaling!
{
	this->MapIDs["Bicheon"] = Maps::Bicheon;
	this->MapIDs["Bicheon Field Entrance"] = Maps::BicheonFringe;
	this->MapIDs["Bullside Forest"] = Maps::BullsideForest;
	this->MapIDs["Demon Bull Temple 1F"] = Maps::DemonBullTemple1F;
	this->MapIDs["Gingko Valley Village"] = 0; //0 means I haven't recorded thd ID yet
	this->MapIDs["Gingko Valley Field"] = 0; 
	this->MapIDs["Gingko Valley Abandoned Mine 1F"] = 0;
	this->MapIDs["Gingko Valley Abandoned Mine 2F"] = 0;
	this->MapIDs["Gingko Valley Abandoned Mine 3F"] = 0;
	this->MapIDs["Snake Pit"] = 0;
	this->MapIDs["Red Name Village"] = 0;
	this->MapIDs["Sinner's Shire"] = 0;
}

bool Tasker::TeleportToMap(char* MapName)
{
	if (MapName == NULL)
		return false;

	uint32_t MapIndex = this->MapIDs[MapName];
	PacketWriter* p = Factory::ChangeMap(MapIndex);

	bool result = PacketBuilder::EncryptAndSend((BYTE*)p->GetBuffer(), p->GetSize());

	delete[] p->GetBuffer();
	delete p;

	return result;
}