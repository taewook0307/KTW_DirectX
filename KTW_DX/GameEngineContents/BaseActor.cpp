#include "PreCompile.h"
#include "BaseActor.h"

#include "Map.h"

BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
}

void BaseActor::GravityOn(float _Delta, float _Force /*= 4000.0f*/)
{
	Transform.AddLocalPosition(GravityForce * _Delta);
	GravityForce.Y -= _Delta * _Force;
}

void BaseActor::GravityReset()
{
	GravityForce = float4::ZERO;
}

void BaseActor::SetGravityForce(const float4& _Value)
{
	GravityReset();
	GravityForce = _Value;
}

float4 BaseActor::GetGravityForce()
{
	return GravityForce;
}

void BaseActor::ActorGravity(float _Delta, float4 _CheckPos, float _Force /*= 4000.0f*/, const GameEngineColor& _DefaultColor /*= GameEngineColor::BLACK*/)
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(_CheckPos, _DefaultColor);

	if (FLOORCOLOR != CheckColor && STOOLCOLOR != CheckColor)
	{
		GravityOn(_Delta, _Force);
	}
	else
	{
		float4 CheckPos = _CheckPos + float4::UP;
		GameEngineColor UpColor = Map::MainMap->GetColor(CheckPos, _DefaultColor);

		while (UpColor == FLOORCOLOR)
		{
			CheckPos = CheckPos + float4::UP;
			UpColor = Map::MainMap->GetColor(CheckPos, _DefaultColor);
			Transform.AddLocalPosition(float4::UP);
		}

		GravityReset();
	}
}

void BaseActor::ActorHalfGravity(float _Delta, float4 _CheckPos)
{
	ActorGravity(_Delta, _CheckPos, 2000.0f);
}