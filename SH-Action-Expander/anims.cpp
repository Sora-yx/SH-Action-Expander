#include "pch.h"
#include <vector>
#include "acts_api.h"

FastStdcallHook<void*, TObjPlayer*> LoadCharacterAnimations_h(0x580060);
FastUsercallHook<int8_t, TObjTeam*> TObjTeamInitTeamMembeonmode_h(0x5AAA80);

struct CustomMML_MOTIONTABLE
{
	signed int id;
	struct RtAnimAnimation* ptr;
	signed int thismotion;
	void* pARAM;
};


DataArray(CustomMML_MOTIONTABLE, player_motions, 0xA47FBC, 777);

constexpr uint16_t AnimFilesCount = 775u;
constexpr uint8_t speedAnimCount = 105u;
constexpr uint8_t flyAnimCount = 93u;
constexpr uint8_t powerAnimCount = 107u;

uint32_t lastAnimSonicID = speedAnimCount;
uint32_t lastAnimShadowID = speedAnimCount;
uint32_t lastAnimAmyID = speedAnimCount;
uint32_t lastAnimEspioID = speedAnimCount;

uint32_t lastAnimMilesID = flyAnimCount;
uint32_t lastAnimRougeID = flyAnimCount;
uint32_t lastAnimCreamID = flyAnimCount;
uint32_t lastAnimCharmyID = flyAnimCount;

uint32_t lastAnimKnuxID = powerAnimCount;
uint32_t lastAnimOmegaID = powerAnimCount;
uint32_t lastAnimBigID = powerAnimCount;
uint32_t lastAnimVectorID = powerAnimCount;

uint32_t lastAnimFileID = AnimFilesCount;

std::vector<PL_MOTION> sonicNewAnimsList;
std::vector<PL_MOTION> shadowNewAnimsList;
std::vector<PL_MOTION> amyNewAnimsList;
std::vector<PL_MOTION> espioNewAnimsList;

std::vector<PL_MOTION> milesNewAnimsList;
std::vector<PL_MOTION> rougeNewAnimsList;
std::vector<PL_MOTION> creamNewAnimsList;
std::vector<PL_MOTION> charmyNewAnimsList;

std::vector<PL_MOTION> knuxNewAnimsList;
std::vector<PL_MOTION> omegaNewAnimsList;
std::vector<PL_MOTION> bigNewAnimsList;
std::vector<PL_MOTION> vectorNewAnimsList;

std::vector<CustomMML_MOTIONTABLE> newPlayerMotions;

// we use a queue system so if this mod is loaded before user register anim, we will copy the new registered anim in the queue later
// this also allow us to make sure the original anims are copy in the vector before the new ones.

struct QueueNewAnimInfo
{
	Character charID;
	PL_MOTION animInfo;
};

std::vector<QueueNewAnimInfo> queueNewRegisteredAnimsList;
std::vector<CustomMML_MOTIONTABLE> queueNewRegisteredAnimFile;


void UpdateAnimList()
{
	
	for (int i = 0; i < speedAnimCount; i++)
	{
		sonicNewAnimsList[i] = sonic_motions[i];
		shadowNewAnimsList[i] = shadow_motions[i];
		amyNewAnimsList[i] = amy_motions[i];
		espioNewAnimsList[i] = espio_motions[i];
	}


	for (int i = 0; i < flyAnimCount; i++)
	{
		milesNewAnimsList[i] = miles_motions[i];
		rougeNewAnimsList[i] = rouge_motions[i];
		creamNewAnimsList[i] = cream_motions[i];
		charmyNewAnimsList[i] = charmy_motions[i];
	}

	for (int i = 0; i < powerAnimCount; i++)
	{
		knuxNewAnimsList[i] = knuckles_motions[i];
		omegaNewAnimsList[i] = omega_motions[i];
		bigNewAnimsList[i] = big_motions[i];
		vectorNewAnimsList[i] = vector_motions[i];
	}

	if (queueNewRegisteredAnimsList.size() > 0)
	{
		for (int i = 0; i < queueNewRegisteredAnimsList.size(); i++)
		{
			auto &info = queueNewRegisteredAnimsList[i];

			switch (info.charID)
			{
			case Char_Sonic:
				sonicNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Shadow:
				shadowNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Amy:
				amyNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Espio:
				espioNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Tails:
				milesNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Rouge:
				rougeNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Cream:
				creamNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Charmy:
				charmyNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Knuckles:
				knuxNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Omega:
				omegaNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Big:
				bigNewAnimsList.push_back(info.animInfo);
				break;
			case Char_Vector:
				vectorNewAnimsList.push_back(info.animInfo);
				break;
			}

		}

		queueNewRegisteredAnimsList.clear();
	}

	WriteData((PL_MOTION**)0x5CC10C, sonicNewAnimsList.data());
	WriteData((PL_MOTION**)0x5CC1CB, shadowNewAnimsList.data());
	WriteData((PL_MOTION**)0x5CC29E, amyNewAnimsList.data());
	WriteData((PL_MOTION**)0x5CC34E, espioNewAnimsList.data());
	WriteData((PL_MOTION**)0x5CC34E, espioNewAnimsList.data());

	WriteData((PL_MOTION**)0x5C1E96, milesNewAnimsList.data());
	WriteData((PL_MOTION**)0x5C1F84, rougeNewAnimsList.data());
	WriteData((PL_MOTION**)0x5C208E, creamNewAnimsList.data());
	WriteData((PL_MOTION**)0x5C2126, charmyNewAnimsList.data());

	WriteData((PL_MOTION**)0x5B8047, knuxNewAnimsList.data());
	WriteData((PL_MOTION**)0x5B817C, omegaNewAnimsList.data());
	WriteData((PL_MOTION**)0x5B8220, bigNewAnimsList.data());
	WriteData((PL_MOTION**)0x5B8307, vectorNewAnimsList.data());
}

void UpdateAnimeFileList()
{
	for (int i = 0; i < 775; i++)
	{
		newPlayerMotions[i] = player_motions[i];	
	}

	if (queueNewRegisteredAnimFile.size() > 0)
	{
		for (auto& anim : queueNewRegisteredAnimFile)
		{
			newPlayerMotions.push_back(anim);
		}

		queueNewRegisteredAnimFile.clear();
	}


	// patch every reference to the player_motions array to use our own vector instead

	//PSetMotion
	WriteData((RtAnimAnimation***)0x5A2370, &newPlayerMotions[0].ptr);
	WriteData((RtAnimAnimation***)0x05A23B5, &newPlayerMotions[0].ptr);
	WriteData((RtAnimAnimation***)0x5A247F, &newPlayerMotions[0].ptr);
	WriteData((RtAnimAnimation***)0x5A27C8, &newPlayerMotions[0].ptr);
	WriteData((RtAnimAnimation***)0x5A2810, &newPlayerMotions[0].ptr);
	WriteData((RtAnimAnimation***)0x5A2997, &newPlayerMotions[0].ptr);

	//PSetMOtion_Next
	WriteData((RtAnimAnimation***)0x5A2B78, &newPlayerMotions[0].ptr);

	//mtnmanwk::GetMotionStartFrameit'
	WriteData((RtAnimAnimation***)0x5A2C73, &newPlayerMotions[0].ptr);

	// PInitializeInterpolateMotion
	WriteData((RtAnimAnimation***)0x5A2CFD, &newPlayerMotions[0].ptr);

	// PTerminateInterpolateMotion
	WriteData((RtAnimAnimation***)0x5A2D66, &newPlayerMotions[0].ptr);

	// TObjOldPlayer::SoundFootSteps
	WriteData((RtAnimAnimation***)0x5A4BD8, &newPlayerMotions[0].ptr);

	// sub_5B72F0 (something related to Omega?)
	WriteData((RtAnimAnimation***)0x5B741F, &newPlayerMotions[0].ptr);

	// sub_5B7A00 (something related to Vector?)
	WriteData((RtAnimAnimation***)0x5B7BA1, &newPlayerMotions[0].ptr);
}

int32_t CheckAndRegisterNewAnim(Character chara, PL_MOTION* mtnInfo, RtAnimAnimation* animData, uint32_t& lastAnimID)
{

	if (queueNewRegisteredAnimsList.size() < UINT32_MAX)
	{
		QueueNewAnimInfo animInfo;
		memset(&animInfo, 0, sizeof(QueueNewAnimInfo));
		animInfo.animInfo = *mtnInfo;
		animInfo.charID = chara;
		queueNewRegisteredAnimsList.push_back(animInfo);
		lastAnimID++;

		if (queueNewRegisteredAnimFile.size() < UINT32_MAX)
		{
			CustomMML_MOTIONTABLE animFile;
			memset(&animFile, 0, sizeof(CustomMML_MOTIONTABLE));
			animFile.id |= 1 << chara;
			animFile.ptr = animData;
			auto* pAram = queueNewRegisteredAnimFile.size() > 0 ? &queueNewRegisteredAnimFile.back() : &player_motions[775];
			pAram->pARAM = (void*)lastAnimFileID;

			queueNewRegisteredAnimFile.push_back(animFile);
			lastAnimFileID++;
			return 0;
		}

	}

	printf("Failed to register new animation, vector size is full....(no way you managed to reach that, something must be wrong.)\n");
	return -1;
}


int RegisterNewAnim(Character chara, const char* animName, PL_MOTION* mtnInfo, RtAnimAnimation* animData, uint32_t* outAnimID, uint32_t* outAnimFileID)
{
	if ((int)chara < 0 || chara > Char_Charmy)
	{
		printf("Failed to register new animation %s, invalid character type sent. %d\n", animName, (int)chara);
		return -1;
	}

	if (!animData)
	{
		printf("Failed to register new animation %s, RtAnimAnimation is null.\n", animName);
		return -1;
	}

	if (!mtnInfo)
	{
		printf("Failed to register new animation %s, PL_MOTION is null.\n", animName);
		return -1;
	}

	int res = -1;
	*outAnimFileID = lastAnimFileID;

	switch (chara)
	{
	case Char_Sonic:

		*outAnimID = lastAnimSonicID;	
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimSonicID);
		break;
	case Char_Shadow:
		*outAnimID = lastAnimShadowID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimShadowID);
		break;
	case Char_Amy:
		*outAnimID = lastAnimAmyID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimAmyID);
		break;
	case Char_Espio:
		*outAnimID = lastAnimEspioID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimEspioID);
		break;
	case Char_Tails:
		*outAnimID = lastAnimMilesID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimMilesID);
		break;
	case Char_Rouge:
		*outAnimID = lastAnimRougeID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimRougeID);
		break;
	case Char_Cream:
		*outAnimID = lastAnimCreamID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimCreamID);
		break;
	case Char_Charmy:
		*outAnimID = lastAnimCharmyID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimCharmyID);
		break;
	case Char_Knuckles:
		*outAnimID = lastAnimKnuxID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimKnuxID);
		break;
	case Char_Omega:
		*outAnimID = lastAnimOmegaID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimOmegaID);
		break;
	case Char_Big:
		*outAnimID = lastAnimBigID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimBigID);
		break;
	case Char_Vector:
		*outAnimID = lastAnimVectorID;
		res = CheckAndRegisterNewAnim(chara, mtnInfo, animData, lastAnimVectorID);
		break;			
	}

	if (res == 0)
	{
		printf("[SH-Action-Expander] Successfully registered new animation %s - id %d for character %d\n", animName, (int)*outAnimID, (int)chara);
	}
	return res;
}


void* __stdcall TObjOldPlayerLoadCharacterAnimations_r(TObjPlayer* TObjPlayer)
{
	auto res = LoadCharacterAnimations_h.Original(TObjPlayer);
	UpdateAnimeFileList();
	return res;
}

signed __int8 TObjTeamInitTeamMember_r(TObjTeam* this_)
{
	UpdateAnimList();
	return TObjTeamInitTeamMembeonmode_h.Original(this_);
}

PL_MOTION* GetNewCharacterAnimationList(const Character chara)
{
	switch (chara)
	{
	case Char_Sonic:
		return sonicNewAnimsList.data();
	case Char_Shadow:
		return shadowNewAnimsList.data();
	case Char_Amy:
		return amyNewAnimsList.data();
	case Char_Espio:
		return espioNewAnimsList.data();
	case Char_Tails:
		return milesNewAnimsList.data();
	case Char_Rouge:
		return rougeNewAnimsList.data();
	case Char_Cream:
		return creamNewAnimsList.data();
	case Char_Charmy:
		return charmyNewAnimsList.data();
	case Char_Knuckles:
		return knuxNewAnimsList.data();
	case Char_Omega:
		return omegaNewAnimsList.data();
	case Char_Big:
		return bigNewAnimsList.data();
	case Char_Vector:
		return vectorNewAnimsList.data();
	}

	return nullptr;
}

MML_MOTIONTABLE* GetNewPlayerMotionList()
{
	return (MML_MOTIONTABLE* )newPlayerMotions.data();
}

int GetNextAvailableAnimID(const Character chara)
{
	switch (chara)
	{
	case Char_Sonic:
		return lastAnimSonicID;
	case Char_Shadow:
		return lastAnimShadowID;
	case Char_Amy:
		return lastAnimAmyID;
	case Char_Espio:
		return lastAnimEspioID;
	case Char_Tails:
		return lastAnimMilesID;
	case Char_Rouge:
		return lastAnimRougeID;
	case Char_Cream:
		return lastAnimCreamID;
	case Char_Charmy:
		return lastAnimCharmyID;
	case Char_Knuckles:
		return lastAnimKnuxID;
	case Char_Omega:
		return lastAnimOmegaID;
	case Char_Big:
		return lastAnimBigID;
	case Char_Vector:
		return lastAnimVectorID;
	}

	return -1;
}

void InitNewAnims()
{

	newPlayerMotions.clear();

	for (int i = 0; i < speedAnimCount; i++)
	{
		sonicNewAnimsList.push_back(sonic_motions[i]);
		shadowNewAnimsList.push_back(shadow_motions[i]);
		amyNewAnimsList.push_back(amy_motions[i]);
		espioNewAnimsList.push_back(espio_motions[i]);
	}


	for (int i = 0; i < flyAnimCount; i++)
	{
		milesNewAnimsList.push_back(miles_motions[i]);
		rougeNewAnimsList.push_back(rouge_motions[i]);
		creamNewAnimsList.push_back(cream_motions[i]);
		charmyNewAnimsList.push_back(charmy_motions[i]);
	}

	for (int i = 0; i < powerAnimCount; i++)
	{
		knuxNewAnimsList.push_back(knuckles_motions[i]);
		omegaNewAnimsList.push_back(omega_motions[i]);
		bigNewAnimsList.push_back(big_motions[i]);
		vectorNewAnimsList.push_back(vector_motions[i]);
	}

	for (int i = 0; i < 775; i++)
	{
		CustomMML_MOTIONTABLE mtnTable;
		memset(&mtnTable, 0, sizeof(CustomMML_MOTIONTABLE));
		newPlayerMotions.push_back(mtnTable);
	}

	UpdateAnimList();

	LoadCharacterAnimations_h.Hook(TObjOldPlayerLoadCharacterAnimations_r);
	TObjTeamInitTeamMembeonmode_h.Hook(TObjTeamInitTeamMember_r, rAL, rESI);

}