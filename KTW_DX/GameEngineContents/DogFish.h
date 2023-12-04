#pragma once

#include "BaseSummonActor.h"

#define DOGFISHJUMPPOWER 1400.0f

#define DOGFISHANIMATIONINTER 0.05f

#define DOGFISHCOLLISIONSCALE { 150.0f, 70.0f }
#define DOGFISHCOLLISIONPOSITION { 0.0f, 35.0f }

class DogFish : public BaseSummonActor
{
public:
	// constrcuter destructer
	DogFish();
	~DogFish();

	// delete Function
	DogFish(const DogFish& _Other) = delete;
	DogFish(DogFish&& _Other) noexcept = delete;
	DogFish& operator=(const DogFish& _Other) = delete;
	DogFish& operator=(DogFish&& _Other) noexcept = delete;

protected:

private:
	float JumpPower = DOGFISHJUMPPOWER;
	void JumpStart();
	void JumpUpdate(float _Delta);
	
	void LandingStart();
	void LandingUpdate(float _Delta);
	
	void MoveStart();
	void MoveUpdate(float _Delta);

	void DeathSoundPlay();
	void DeathStart();
	void DeathUpdate(float _Delta);

private:
	int Life = 3;
	float Speed = 600.0f;

	EDOGFISHSTATE CurState = EDOGFISHSTATE::None;
	std::string State = "";

	void StateUpdate(float _Delta);
	void ChangeState(EDOGFISHSTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	void CreateDeathEffect();

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> DogFishRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;
};