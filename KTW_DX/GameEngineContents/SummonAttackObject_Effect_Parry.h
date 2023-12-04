#pragma once

#include "SummonAttackObject_Effect.h"

class SummonAttackObject_Effect_Parry : public SummonAttackObject_Effect
{
public:
	// constrcuter destructer
	SummonAttackObject_Effect_Parry();
	~SummonAttackObject_Effect_Parry();

	// delete Function
	SummonAttackObject_Effect_Parry(const SummonAttackObject_Effect_Parry& _Other) = delete;
	SummonAttackObject_Effect_Parry(SummonAttackObject_Effect_Parry&& _Other) noexcept = delete;
	SummonAttackObject_Effect_Parry& operator=(const SummonAttackObject_Effect_Parry& _Other) = delete;
	SummonAttackObject_Effect_Parry& operator=(SummonAttackObject_Effect_Parry&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};