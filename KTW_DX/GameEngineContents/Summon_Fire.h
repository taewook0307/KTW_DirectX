#pragma once

#include "DevilSummonActor.h"

class Summon_Fire : public DevilSummonActor
{
public:
	// constrcuter destructer
	Summon_Fire();
	~Summon_Fire();

	// delete Function
	Summon_Fire(const Summon_Fire& _Other) = delete;
	Summon_Fire(Summon_Fire&& _Other) noexcept = delete;
	Summon_Fire& operator=(const Summon_Fire& _Other) = delete;
	Summon_Fire& operator=(Summon_Fire&& _Other) noexcept = delete;

protected:

private:

};