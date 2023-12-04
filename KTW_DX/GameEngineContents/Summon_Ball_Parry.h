#pragma once

#include "Summon_Ball.h"

class Summon_Ball_Parry : public Summon_Ball
{
public:
	// constrcuter destructer
	Summon_Ball_Parry();
	~Summon_Ball_Parry();

	// delete Function
	Summon_Ball_Parry(const Summon_Ball_Parry& _Other) = delete;
	Summon_Ball_Parry(Summon_Ball_Parry&& _Other) noexcept = delete;
	Summon_Ball_Parry& operator=(const Summon_Ball_Parry& _Other) = delete;
	Summon_Ball_Parry& operator=(Summon_Ball_Parry&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};