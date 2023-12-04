#pragma once

#include "Summon_Fire.h"

class Summon_Fire_Parry : public Summon_Fire
{
public:
	// constrcuter destructer
	Summon_Fire_Parry();
	~Summon_Fire_Parry();

	// delete Function
	Summon_Fire_Parry(const Summon_Fire_Parry& _Other) = delete;
	Summon_Fire_Parry(Summon_Fire_Parry&& _Other) noexcept = delete;
	Summon_Fire_Parry& operator=(const Summon_Fire_Parry& _Other) = delete;
	Summon_Fire_Parry& operator=(Summon_Fire_Parry&& _Other) noexcept = delete;

protected:
	
private:
	void Start() override;
};