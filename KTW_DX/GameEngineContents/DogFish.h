#pragma once

#include "BaseActor.h"

#define DOGFISHJUMPPOWER 1400.0f

class DogFish : public BaseActor
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

	void DeathStart();
	void DeathUpdate(float _Delta);

private:
	EDOGFISHSTATE CurState = EDOGFISHSTATE::None;
	std::string State = "";

	void StateUpdate(float _Delta);
	void ChangeState(EDOGFISHSTATE _State);
	void ChangeAnimation(std::string_view _State);

	float Speed = 400.0f;
	void DogFishMove();

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;
};