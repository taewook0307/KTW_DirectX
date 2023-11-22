#pragma once

#include "DevilSummonActor.h"

#define SUMMONDEVILCOLLISIONSCALE { 125.0f, 150.0f }
#define SUMMONDEVILCOLLISIONPOSITIONLEFT { 180.0f, 90.0f }
#define SUMMONDEVILCOLLISIONPOSITIONRIGHT { -180.0f, 90.0f }

class SummonDevil : public DevilSummonActor
{
public:
	// constrcuter destructer
	SummonDevil();
	~SummonDevil();

	// delete Function
	SummonDevil(const SummonDevil& _Other) = delete;
	SummonDevil(SummonDevil&& _Other) noexcept = delete;
	SummonDevil& operator=(const SummonDevil& _Other) = delete;
	SummonDevil& operator=(SummonDevil&& _Other) noexcept = delete;

	void SetStartDirRight();

protected:

private:
	float Speed = 300.0f;
	EACTORDIR Dir = EACTORDIR::Left;

	std::shared_ptr<GameEngineSpriteRenderer> SummonDevilRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SummonDevilEffectRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> SummonDevilCollision = nullptr;
	GameEngineState SummonDevilState;

	void Start() override;
	void Update(float _Delta) override;

	void DirChange();
	bool CameraOutCheck();

	void SummonDevilMove(float _Delta);
	void PosSetting();

	void HitCheck();

	void SpawnSoundPlay();
	void DeathSoundPlay();
};