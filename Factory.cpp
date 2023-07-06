#include "Factory.hpp"

PacketWriter* Factory::Fishing(uint32_t fishingLocationHash, byte bStage, byte bUnk1)
{
	PacketWriter* p = new PacketWriter(Opcodes::Fishing);
	p->Write<uint32_t>(fishingLocationHash);
	p->Write<uint32_t>(0);
	p->Write<byte>(bStage);
	p->Write<byte>(bUnk1);
	return p;
}

PacketWriter* Factory::RepairItems(uint64_t npcHash, uint64_t itemHash, byte bRepairingAll, byte nItemsToRepair)
{
	PacketWriter* p = new PacketWriter(Opcodes::TalkNPC);
	p->Write<uint64_t>(npcHash);
	p->Write<uint64_t>(itemHash);
	p->Write<byte>(bRepairingAll);
	p->Write<byte>(nItemsToRepair);
	return p;
}

PacketWriter* Factory::ChangeMap(uint32_t MapIndex)
{
	PacketWriter* p = new PacketWriter(Opcodes::ChangeMap);
	p->Write<uint32_t>(MapIndex);
	return p;
}

PacketWriter* Factory::Attack(uint32_t skillID, uint16_t sUnk1, uint64_t Hash1, uint32_t dUnk1, uint16_t nMonstersAttacked, uint64_t* attackedHashList)
{
	sUnk1 = 4; //constant, will find why later

	PacketWriter* p = new PacketWriter(Opcodes::Attack);
	p->Write<uint32_t>(skillID);
	p->Write<uint16_t>(sUnk1);
	p->Write<uint64_t>(Hash1);
	p->Write<uint32_t>(dUnk1);
	p->Write<uint16_t>(nMonstersAttacked);

	for (int i = 0; i < nMonstersAttacked; i++)
	{
		p->Write<uint64_t>(attackedHashList[i]);
	}

	return p;
}