#pragma once

#include "BaseBoss.h"

class Devil : public BaseBoss
{
public:
	// constrcuter destructer
	Devil();
	~Devil();

	// delete Function
	Devil(const Devil& _Other) = delete;
	Devil(Devil&& _Other) noexcept = delete;
	Devil& operator=(const Devil& _Other) = delete;
	Devil& operator=(Devil&& _Other) noexcept = delete;

protected:

private:
	GameEngineState DevilState;
};