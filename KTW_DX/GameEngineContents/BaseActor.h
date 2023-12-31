#pragma once

#define GRAVITYFORCE 4000.0f
#define GRAVITYHALFFORCE GRAVITYFORCE * 0.5f

#define EMPTYCOLOR GameEngineColor::WHITE
#define FLOORCOLOR GameEngineColor::BLACK
#define STOOLCOLOR GameEngineColor::BLUE
#define MAPOUTCOLOR GameEngineColor::RED

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

	void GravityOn(float _Delta, float _Force = 4000.0f);
	void GravityReset();

	void SetGravityForce(const float4& _Value);
	float4 GetGravityForce();

	virtual void ActorGravity(float _Delta, float4 _CheckPos, float _Force = 4000.0f, const GameEngineColor& _DefaultColor = GameEngineColor::BLACK);
	void ActorHalfGravity(float _Delta, float4 _CheckPos);
protected:

private:
	float4 GravityForce = float4::ZERO;
};