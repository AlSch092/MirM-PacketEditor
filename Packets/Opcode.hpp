//Alsch092 @Github 
//March 2 2023
#pragma once

//not a full list but this will be the majority of them
namespace Opcodes
{
	enum Send
	{
		Movement = 0x11, 
		StoryModeMovement = 0x365,
		Attack = 0x17,   
		PlayerGesture = 0x1D, 

		SetPowerScore = 0x21, 
		CompleteTutorial = 0x2CD,

		UpgradeSkill = 0xDF, 
		Craft = 0x53, 

		EnchantItem = 0x463, 
		UnlockDragonsteelSocket = 0x1E5, 

		TalkNPC = 0x21, 
		PurchaseNPCItem = 0x31, 
		IntamacyNPCReward = 0x369,

		ItemBlessing = 0x45,  
		ItemEnhance = 0x49, 
		ConsumePotion = 0x4D, 

		ChangeMap = 0x5F,
		EnterStoryDungeon = 0x35F, 
		UseSoaringStone = 0x7B,
		TeleportToMapWithXYZ = 0x379,

		PlayerSpeak = 0x10D,
		TargetMonster = 0x6D,

		CreateClan = 0x7F, 
		JoinClan = 0x81, 
		DonateClan = 0x127, 
		InviteClan = 0x2CF,  
		OrderClanMission = 0x22B,

		MarketItemSettlement = 0x0107, 

		EnterRealm = 0x2C1,   
		ChargeHours = 0x3C1, 
		OnSpawnInRealm = 0x43B,

		Gathering = 0x73,
		Fishing = 0xF1, 

		ChangePVPMode = 0x10F, 

		UseCharacterAvatarTicket = 0x21,  
		SummonAvatar = 0x3CF, 

		StartQuest = 0xE5, 
		ProceedQuest = 0xE7, 
		FinishQuest = 0xEB, 

		OpenMail = 0x111,		  
		CollectMailReward = 0x113,
		DeleteMail = 0x115,		   

		UseSpriritTicket = 0x24F,  
		RegisterSpirit = 0x23F,    

		EquipTitle = 0x25D, 

		SkipCutscene = 0x00E5,
		ReceiveQuestReward = 0x00EB,
		ReceiveXReward = 0x2E5,

		OpenStreetStall = 0x43F, 

		CastSpell = 0x36B,

		Revive = 0x387,

		PickMentor = 0x29B, 

		TrainInnerForce = 0x405,

		SummonMount = 0x00D3, 
		EquipMount = 0x247,
		FeedMount = 0x249,

		LockItem = 0x3B3,

		SpawnMonstersStoryMode = 0x363,

		LinkWemixWallet = 0x4AF, 
		WalletSignedMsg = 0x4B9,
		ClaimStakingReward = 0x4CD,
		VoteWithDogma = 0x4CF, 
		Unknown = 0x4BB, 
		WalletSettleItem = 0x4C3, 
		
		ChargeVigor = 0x471,

		PurchaseCashShopItem = 0x2F5, 

		AllocateMandalaNode = 0x407, 

		RepairItems = 0x15F, 

		CombineAvatars = 0x3D1, 
		AutoMatchPartyDungeon = 0xBF,
		CancelPartySearch = 0x15D,
		EnterPartyDungeon = 0xC1, 

		SendFriendRequest = 0x28F,
		
		RegisterCodex = 0x2A9, 

		PostMentorAd = 0x299,
		RequestMentor = 0x29B,

		OpenTreasureChest = 0x235,

		ParticipateRumble = 0x3F9,
		CancelJoinRumble = 0x3FB,
		QueueRumble = 0x45F,
	};

  //will get the rest of these later
	enum Recv
	{
		MonsterMovement = 0x16, 
	
		OnPlayerAttackedMonster = 0x1A, 
		OnPlayerSpeak = 0x10E,  

		GainExperience = 0x24,
		UpdateCopperCount = 0x6E,
	};
}
