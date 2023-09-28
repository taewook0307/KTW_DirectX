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
		if (true == IsIntroState)
		{
			return;
		}

		++HitCount;
	}

protected:
	EBOSSPHASE CurPhase = EBOSSPHASE::Phase1;
	bool IsIntroState = false;

	int HitCount = 0;

private:

};