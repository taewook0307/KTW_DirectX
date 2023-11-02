#pragma once

#define DEVILANIMATIONINTER 0.05f

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

	int FireIndex = 0;
	float FireMoveTimer = 1.0f;
	void CreateFire();
	void FireMoveReq(float _Delta);

	float BallMoveTimer = 1.0f;
	void CreateBall();
	void BallMoveReq(float _Delta);

	bool SummonDeathCheck();
	std::vector<std::shared_ptr<class DevilSummonActor>> SummonActors;

	EACTORDIR SerpentDir = EACTORDIR::Left;
	void ChangeSerpentDir();

	bool SummonAttackBall = false;

private:
	std::shared_ptr<GameEngineSpriteRenderer> DevilRenderer = nullptr;

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