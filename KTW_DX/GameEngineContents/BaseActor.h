#pragma once

#include <GameEngineCore/GameEngineActor.h>

#define GRAVITYFORCE 4000.0f

#define EMPTYCOLOR GameEngineColor { 255, 255, 255, 255 }
#define FLOORCOLOR GameEngineColor { 0, 0, 0, 255 }
#define STOOLCOLOR GameEngineColor { 0, 0, 255, 255 }

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

	virtual void ActorGravity(float _Delta, float4 _CheckPos);
protected:

private:
	float4 GravityForce = float4::ZERO;
};