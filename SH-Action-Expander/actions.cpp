#include "pch.h"
#include <vector>
#include "acts_api.h"

uint32_t lastModeSpeedID = 90;
uint32_t lastModeFlyID = 90;
uint32_t lastModePowerID = 90;

std::vector<uint32_t> newModesSpeed;
std::vector<uint32_t> newModesFly;
std::vector<uint32_t> newModesPower;

// for check Input
uint32_t lastSModeSpeedID = 90;
uint32_t lastSModeFlyID = 90;
uint32_t lastSModePowerID = 90;

std::vector<uint32_t> newSModeSpeed;
std::vector<uint32_t> newSModeFly;
std::vector<uint32_t> newSModePower;

// team mode
uint32_t lastTeamPlayModeID = 30;
uint32_t lastPrevTeamPlayMode = 30;

std::vector<uint32_t> newPrevModesTeamPlay;
std::vector<uint32_t> newModesTeamPlay;

int32_t CheckAndRegisterNewAction(std::vector<uint32_t>* vecMode, uint32_t& lastModeID)
{
	if (vecMode->size() < UINT32_MAX)
	{
		vecMode->push_back(lastModeID);
		lastModeID++;
		return vecMode->back();
	}

	printf("Failed to register new action, vector size is full....(no way you managed to reach that, something must be wrong.)\n");
	return -1;
}


int32_t RegisterNewCharacterMode(charaType type)
{
	if (type > powerType || type < speedType)
	{
		printf("Failed to register new action (mode), invalid character type sent. %d\n", (int)type);
		return -1;
	}

	if (speedType)
	{
		return CheckAndRegisterNewAction(&newModesSpeed, lastModeSpeedID);
	}

	if (flyType)
	{
		return CheckAndRegisterNewAction(&newModesFly, lastModeFlyID);
	}

	return CheckAndRegisterNewAction(&newModesPower, lastModePowerID);
}

int32_t RegisterNewCharacterSMode(charaType type)
{
	if (type > powerType || type < speedType)
	{
		printf("Failed to register new Smode (chk input), invalid character type sent. %d\n", (int)type);
		return -1;
	}

	if (speedType)
	{
		return CheckAndRegisterNewAction(&newSModeSpeed, lastSModeSpeedID);
	}

	if (flyType)
	{
		return CheckAndRegisterNewAction(&newSModeFly, lastSModeFlyID);
	}

	return CheckAndRegisterNewAction(&newSModePower, lastSModePowerID);
}


int32_t RegisterNewTeamPlayMode()
{
	return CheckAndRegisterNewAction(&newModesTeamPlay, lastTeamPlayModeID);
}

int32_t RegisterNewLastTeamPlayMode()
{
	return CheckAndRegisterNewAction(&newPrevModesTeamPlay, lastPrevTeamPlayMode);
}

void InitActionsExpander()
{

}

