#pragma once

#include <GameEngineCore/GameEngineActor.h>

class PirateBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	PirateBullet();
	~PirateBullet();

	// delete Function
	PirateBullet(const PirateBullet& _Other) = delete;
	PirateBullet(PirateBullet&& _Other) noexcept = delete;
	PirateBullet& operator=(const PirateBullet& _Other) = delete;
	PirateBullet& operator=(PirateBullet&& _Other) noexcept = delete;

protected:
	float4 DirVector = float4::LEFT;
	float4 PlayerPos = float4::ZERO;

private:
	float Speed = 500.0f;
	std::shared_ptr<GameEngineSpriteRenderer> BulletRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BulletCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};