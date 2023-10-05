#pragma once

#include "BaseActor.h"

#define CANNONCOLLISIONSCALE { 90.0f, 90.0f }
#define CANNONCOLLISIONPOSITION { 45.0f, 45.0f }

class CannonBall : public BaseActor
{
public:
	// constrcuter destructer
	CannonBall();
	~CannonBall();

	// delete Function
	CannonBall(const CannonBall& _Other) = delete;
	CannonBall(CannonBall&& _Other) noexcept = delete;
	CannonBall& operator=(const CannonBall& _Other) = delete;
	CannonBall& operator=(CannonBall&& _Other) noexcept = delete;

protected:

private:
	float Speed = 700.0f;

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;
};