#pragma once

void InitNewAnims();
PL_MOTION* GetNewCharacterAnimationList(const Character chara);
MML_MOTIONTABLE* GetNewPlayerMotionList();
int GetNextAvailableAnimID(const Character chara);
int RegisterNewAnim(Character chara, const char* animName, PL_MOTION* mtnInfo, RtAnimAnimation* animData, uint32_t* outAnimID, uint32_t* outAnimFileID);