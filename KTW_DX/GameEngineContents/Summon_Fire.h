#pragma once

#include "SummonAttackObject.h"

class Summon_Fire : public SummonAttackObject
{
public:
	// constrcuter destructer
	Summon_Fire();
	~Summon_Fire();

	// delete Function
	Summon_Fire(const Summon_Fire& _Other) = delete;
	Summon_Fire(Summon_Fire&& _Other) noexcept = delete;
	Summon_Fire& operator=(const Summon_Fire& _Other) = delete;
	Summon_Fire& operator=(Summon_Fire&& _Other) noexcept = delete;

protected:

private:
	float Speed = 500.0f;
	float4 DirPos = float4::ZERO;

	std::shared_ptr<GameEngineSpriteRenderer> FireRenderer = nullptr;

	GameEngineState FireState;

	void Start() override;
	void Update(float _Delta);

	void DirPosSetting();

	bool CameraOutCheck();
};