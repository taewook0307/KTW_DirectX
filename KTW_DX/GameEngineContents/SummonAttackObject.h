#pragma once

#include "DevilSummonActor.h"

class SummonAttackObject : public DevilSummonActor
{
public:
	// constrcuter destructer
	SummonAttackObject();
	~SummonAttackObject();

	// delete Function
	SummonAttackObject(const SummonAttackObject& _Other) = delete;
	SummonAttackObject(SummonAttackObject&& _Other) noexcept = delete;
	SummonAttackObject& operator=(const SummonAttackObject& _Other) = delete;
	SummonAttackObject& operator=(SummonAttackObject&& _Other) noexcept = delete;

protected:
	void CreateSummonEffect(const float4& _Pos);

private:

};