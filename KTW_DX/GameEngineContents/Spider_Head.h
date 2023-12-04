#pragma once

#include "BaseSummonActor.h"

#define SPIDERCOLLISIONSCALE { 240.0f, 140.0f }
#define SPIDERCOLLISIONPOSITION { 0.0f, 110.0f }

class Spider_Head : public BaseSummonActor
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
	float JumpPower = 1500.0f;
	int LandCount = 0;
	void LandCountCheck();

	std::shared_ptr<GameEngineSpriteRenderer> SpiderRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> SpiderCollision = nullptr;
	GameEngineState SpiderState;

	void Start() override;
	void Update(float _Delta) override;

	void FallSoundPlay();
	void LandSoundPlay();
};