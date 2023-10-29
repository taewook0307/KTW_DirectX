#include "PreCompile.h"
#include "BaseActor.h"

#include "Map.h"

BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
}

void BaseActor::GravityOn(float _Delta)
{
	Transform.AddLocalPosition(GravityForce * _Delta);
	GravityForce.Y -= _Delta * GRAVITYFORCE;
}

void BaseActor::GravityHalfOn(float _Delta)
{
	Transform.AddLocalPosition(GravityForce * _Delta);
	GravityForce.Y -= _Delta * GRAVITYHALFFORCE;
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

void BaseActor::ActorGravity(float _Delta, float4 _CheckPos)
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(_CheckPos, FLOORCOLOR);

	if (FLOORCOLOR != CheckColor && STOOLCOLOR != CheckColor)
	{
		GravityOn(_Delta);
	}
	else
	{
		float4 CheckPos = _CheckPos + float4::UP;
		GameEngineColor UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

		while (UpColor == FLOORCOLOR)
		{
			CheckPos = CheckPos + float4::UP;
			UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);
			Transform.AddLocalPosition(float4::UP);
		}

		GravityReset();
	}
}

void BaseActor::ActorHalfGravity(float _Delta, float4 _CheckPos)
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(_CheckPos, FLOORCOLOR);

	if (FLOORCOLOR != CheckColor && STOOLCOLOR != CheckColor)
	{
		GravityHalfOn(_Delta);
	}
	else
	{
		float4 CheckPos = _CheckPos + float4::UP;
		GameEngineColor UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

		while (UpColor == FLOORCOLOR)
		{
			CheckPos = CheckPos + float4::UP;
			UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);
			Transform.AddLocalPosition(float4::UP);
		}

		GravityReset();
	}
}