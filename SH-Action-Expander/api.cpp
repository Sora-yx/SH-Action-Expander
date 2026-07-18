#include "pch.h"
#include "acts_api.h"
#include "actions.h"

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