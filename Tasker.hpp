#pragma once
#include "Factory.hpp"
#include "enums.hpp"
#include <unordered_map>
using namespace std;

class Tasker
{

public:

	void InitializeMapIDs();
	bool TeleportToMap(char* MapName);

	static void SpamFishing(Tasker* pThis);
	
	uint32_t FishingHash = 0;
	bool IsFishingExploit = false; //patched, dont bother
	int FishingRepeats = 50;

	bool EchoPackets = false;

	unordered_map<string, uint32_t> MapIDs;

	char* ScriptBuffer;

};