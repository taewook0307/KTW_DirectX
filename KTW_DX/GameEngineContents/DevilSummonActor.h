#pragma once

#include "BaseBoss.h"

class DevilSummonActor : public BaseBoss
{
public:
	// constrcuter destructer
	DevilSummonActor();
	~DevilSummonActor();

	// delete Function
	DevilSummonActor(const DevilSummonActor& _Other) = delete;
	DevilSummonActor(DevilSummonActor&& _Other) noexcept = delete;
	DevilSummonActor& operator=(const DevilSummonActor& _Other) = delete;
	DevilSummonActor& operator=(DevilSummonActor&& _Other) noexcept = delete;

	virtual void ChangeLeftDir() {}

	virtual void ChangeStateReq() {}
protected:

private:

};