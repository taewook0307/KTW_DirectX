#pragma once

#include "BaseActor.h"

class BaseBoss : public BaseActor
{
public:
	// constrcuter destructer
	BaseBoss();
	~BaseBoss();

	// delete Function
	BaseBoss(const BaseBoss& _Other) = delete;
	BaseBoss(BaseBoss&& _Other) noexcept = delete;
	BaseBoss& operator=(const BaseBoss& _Other) = delete;
	BaseBoss& operator=(BaseBoss&& _Other) noexcept = delete;

	void PlusHitCount()
	{
		++HitCount;
	}

protected:
	void BossGravity(float4 _CheckPos, float _Delta);

	BossPhase CurPhase = BossPhase::Phase1;
	int HitCount = 0;
private:

};