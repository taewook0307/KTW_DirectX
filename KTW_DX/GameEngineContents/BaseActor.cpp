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
	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GravityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GravityForce * _Delta);
	}
	else
	{
		GravityForce = float4::ZERO;
	}
}
