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