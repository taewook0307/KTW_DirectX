#pragma once

#include "BaseActor.h"

class BaseSummonActor : public BaseActor
{
public:
	// constrcuter destructer
	BaseSummonActor();
	~BaseSummonActor();

	// delete Function
	BaseSummonActor(const BaseSummonActor& _Other) = delete;
	BaseSummonActor(BaseSummonActor&& _Other) noexcept = delete;
	BaseSummonActor& operator=(const BaseSummonActor& _Other) = delete;
	BaseSummonActor& operator=(BaseSummonActor&& _Other) noexcept = delete;

	virtual void ChangeLeftDir() {}

	virtual void ChangeStateReq() {}

protected:

private:

};