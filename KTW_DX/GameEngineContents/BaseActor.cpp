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
	GravityForce.Y -= _Delta * GRAVITYFORCE;
	Transform.AddLocalPosition(GravityForce * _Delta);
}

void BaseActor::GravityReset()
{
	GravityForce = float4::ZERO;
}

void BaseActor::SetGravityForce(const float4& _Value)
{
	GravityForce = _Value;
}

float4 BaseActor::GetGravityForce()
{
	return GravityForce;
}