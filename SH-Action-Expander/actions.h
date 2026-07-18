#pragma once



int32_t CheckAndRegisterNewAction(std::vector<uint32_t>* vecMode, uint32_t& lastModeID);
int32_t RegisterNewCharacterMode(charaType type);
int32_t RegisterNewCharacterSMode(charaType type);
int32_t RegisterNewTeamPlayMode();
int32_t RegisterNewLastTeamPlayMode();