#pragma once

#include "DevilSummonActor.h"

#define SERPENTENDPOINTRATIO 0.25f

#define SERPENTCOLLISIONSCALE { 1500.0f, 370.0f }
#define SERPENTCOLLISIONPOSISIONRIGHT { -960.0f, 280.0f }
#define SERPENTCOLLISIONPOSISIONLEFT { 960.0f, 280.0f }

class Serpent_Head : public DevilSummonActor
{
public:
	// constrcuter destructer
	Serpent_Head();
	~Serpent_Head();

	// delete Function
	Serpent_Head(const Serpent_Head& _Other) = delete;
	Serpent_Head(Serpent_Head&& _Other) noexcept = delete;
	Serpent_Head& operator=(const Serpent_Head& _Other) = delete;
	Serpent_Head& operator=(Serpent_Head&& _Other) noexcept = delete;


protected:

private:
	EACTORDIR SerpentDir = EACTORDIR::Right;
	float Speed = 280.0f;
	float MoveEndPoint = 0.0f;

	GameEngineState SerpentState;
	std::shared_ptr<GameEngineSpriteRenderer> SerpentRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> SerpentCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void SerpentMove(float _Delta);
	bool MoveEndCheck();
	void ChangeLeftDir() override;
};