#pragma once

#define DEVILANIMATIONINTER 0.05f
#define DEVILCOLLISIONSCALE { 130.0f, 130.0f }
#define DEVILCOLLISIONPOSITION { 0.0f, 450.0f }
#define IDLETIMER 2.0f

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
	void CreateRamArm();
	void CreateSpiderHead();
	void CreateSerpentHead();
	void CreateFire();
	void CreateBall();

	bool SummonDeathCheck();
	std::vector<std::shared_ptr<class DevilSummonActor>> SummonActors;

	bool SummonAttackBall = false;

	bool AllChangeMove = false;

	int FireIndex = 0;
	void FireMoveReq(float _Delta);
	void BallMoveReq(float _Delta);

	EACTORDIR SerpentDir = EACTORDIR::Left;
	void ChangeSerpentDir();

	void HitCountCheck();

	float IdleTimer = IDLETIMER;
	float FireMoveTimer = 1.0f;
	float BallMoveTimer = 1.0f;
private:
	std::shared_ptr<GameEngineSpriteRenderer> DevilRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> DevilCollision = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> EyeRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HeadRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> TridentRenderer = nullptr;

	GameEngineState DevilState;

	void Start() override;
	void Update(float _Delta) override;

	void EyeRendererSetting();
	void BodyRendererSetting();
	void HeadRendererSetting();
	void TridentRendererSetting();
};