#pragma once

enum Maps
{
	Bicheon = 0x0FE291,
	BicheonFringe = 0x0FBB78,
	NefCave2F = 0x2088A3,
	NefCave3F = 0x20618A,
	DemonBullTempleEntrance = 0x2A4F23,
	DemonBullTemple1F = 0x10CD2E,
	BullsideForest = 0x0FE293,
	RedNameVillage = 0x0FE294,
};

enum Avatars
{
};

enum Mounts
{
	Tiger = 0x2711, //same as tutorial quest ID

};

enum Quests
{
	Tutorial1 = 0x2711, //10001
	Tutorial2 = 0x2712,
};

enum NPCS
{
};

enum Realms
{
	PhantasmicMystic = 0x23,
	SealedTower = 0x28
};

enum Skills //probably this is a hash or packed in some way
{
	LeftSwingAttack = 0x0F4A75,
	RightSwingAttack = 0x0F4A76,
	GreatExplosion = 0x0F4ADC,

	SwordLeftAttack = 0x0F468D,
	SwordRightAttack = 0x0F468E,
};

enum CodexMajor  //first bytes in codex packet denote the LIST ITEM selected (Bicheon, Gingko Valley, Profession, War, etc)
{
	WarBreaksOut1 = 0x2739,
};

enum CodexMinor //next bytes denote which 'window' in the list is selected. (Revealed monsters, waypoint, etc)
{

};