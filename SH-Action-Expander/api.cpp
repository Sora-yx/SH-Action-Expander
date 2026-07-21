#include "pch.h"
#include "acts_api.h"
#include "actions.h"
#include "anims.h"

int32_t ActExp_RegisterNewCharacterMode(charaType type)
{
	return RegisterNewCharacterMode(type);
}

int32_t ActExp_RegisterNewCharacterSMode(charaType type)
{
	return RegisterNewCharacterSMode(type);
}

int32_t ActExp_RegisterNewTeamPlayMode()
{
	return RegisterNewTeamPlayMode();
}

int32_t ActExp_RegisterNewLastTeamPlayMode()
{
	return RegisterNewLastTeamPlayMode();
}

int32_t ActExp_RegisterNewAnimation(Character chara, const char* animName, PL_MOTION* mtnInfo, RtAnimAnimation* animData, uint32_t* outAnimID, uint32_t* outAnimFileID)
{
	return RegisterNewAnim(chara, animName, mtnInfo, animData, outAnimID, outAnimFileID);
}

PL_MOTION* ActExp_GetNewCharacterAnimationList(const Character chara)
{
	return GetNewCharacterAnimationList(chara);
}

MML_MOTIONTABLE* ActExp_GetNewPlayerMotionList()
{
	return GetNewPlayerMotionList();
}

int ActExp_GetNextAvailableAnimID(const Character chara)
{
	return GetNextAvailableAnimID(chara);
}