#pragma once

#include "SummonAttackObject.h"

#define BALLCOLLISIONSCALE { 75.0f, 75.0f }

class Summon_Ball : public SummonAttackObject
{
public:
	// constrcuter destructer
	Summon_Ball();
	~Summon_Ball();

	// delete Function
	Summon_Ball(const Summon_Ball& _Other) = delete;
	Summon_Ball(Summon_Ball&& _Other) noexcept = delete;
	Summon_Ball& operator=(const Summon_Ball& _Other) = delete;
	Summon_Ball& operator=(Summon_Ball&& _Other) noexcept = delete;

protected:

private:
	float Speed = 500.0f;
	float4 DirPos = float4::ZERO;

	int Count = 0;

	std::shared_ptr<GameEngineSpriteRenderer> BallRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BallCollision = nullptr;

	GameEngineState BallState;

	void Start() override;
	void Update(float _Delta) override;

	void DirPosSetting();
	void ChangeDirPos(const float4& _Pos);
	void BallMove(float _Delta);

	void ChangeStateReq() override;

};