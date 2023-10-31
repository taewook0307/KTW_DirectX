#pragma once

#include "DevilSummonActor.h"

class Spider_Head : public DevilSummonActor
{
public:
	// constrcuter destructer
	Spider_Head();
	~Spider_Head();

	// delete Function
	Spider_Head(const Spider_Head& _Other) = delete;
	Spider_Head(Spider_Head&& _Other) noexcept = delete;
	Spider_Head& operator=(const Spider_Head& _Other) = delete;
	Spider_Head& operator=(Spider_Head&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> SpiderRenderer = nullptr;
	GameEngineState SpiderState;

	void Start() override;
	void Update(float _Delta) override;
};