#pragma once

#include <GameEngineCore/GameEngineActor.h>

class BaseActor : public GameEngineActor
{
public:
	// constrcuter destructer
	BaseActor();
	~BaseActor();

	// delete Function
	BaseActor(const BaseActor& _Other) = delete;
	BaseActor(BaseActor&& _Other) noexcept = delete;
	BaseActor& operator=(const BaseActor& _Other) = delete;
	BaseActor& operator=(BaseActor&& _Other) noexcept = delete;

	void GravityOn(float _Delta);
	void GravityReset();

	void SetGravityForce(const float4& _Value);
	float4 GetGravityForce();
protected:

private:
	float4 GravityForce = float4::ZERO;
};