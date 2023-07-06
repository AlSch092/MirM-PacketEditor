#pragma once
#include "PacketBuilder.hpp"

namespace Factory
{
	PacketWriter* Fishing(uint32_t fishingLocationHash, byte bStage, byte bUnk1);
	PacketWriter* ChangeMap(uint32_t MapIndex);
	PacketWriter* RepairItems(uint64_t npcHash, uint64_t itemHash, byte bRepairingAll, byte nItemsToRepair); //check last byte, repair all = 3
	PacketWriter* Attack(uint32_t skillID, uint16_t sUnk1, uint64_t Hash1, uint32_t dUnk1, uint16_t nMonstersAttacked, uint64_t* attackedHashList);
}