#include "PreCompile.h"
#include "DogFish.h"

#include "Map.h"

void DogFish::JumpStart()
{
	ChangeAnimation("Jump");
	SetGravityForce(float4::UP * JumpPower);
}

void DogFish::JumpUpdate(float _Delta)
{
	//애니메이션
	float GravityValue = GetGravityForce().Y;

	if (GravityValue < 30.0f && true == Renderer->IsCurAnimation("DogFish_Jump"))
	{
		Renderer->ChangeAnimation("DogFish_JumpToFall");
	}

	if (GravityValue < 0.0f && true == Renderer->IsCurAnimation("DogFish_JumpToFall"))
	{
		Renderer->ChangeAnimation("DogFish_Fall");
	}

	// 이동
	float4 MovePos = float4::LEFT * Speed * _Delta;
	Transform.AddLocalPosition(MovePos);

	// 점프
	float4 CheckPos = float4::ZERO;

	if (GetGravityForce().Y > 0.0f)
	{
		CheckPos = { 0.0f, 100.0f };
	}

	CheckPos += Transform.GetWorldPosition();

	GameEngineColor CheckColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

	if (FLOORCOLOR != CheckColor)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(EDOGFISHSTATE::Landing);
		return;
	}
}

void DogFish::LandingStart()
{
	ChangeAnimation("Landing");
}

void DogFish::LandingUpdate(float _Delta)
{
	float4 CheckPos = Transform.GetWorldPosition() + float4::UP;
	GameEngineColor UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

	while (UpColor == FLOORCOLOR)
	{
		CheckPos = Transform.GetWorldPosition() + float4::UP;
		UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);
		Transform.AddLocalPosition(float4::UP);
	}
}

void DogFish::MoveStart()
{
	ChangeAnimation("Move");
}

void DogFish::MoveUpdate(float _Delta)
{
	// 이동
	float4 MovePos = float4::LEFT * Speed * _Delta;
	Transform.AddLocalPosition(MovePos);

	float4 Pos = Transform.GetWorldPosition();
	if (Pos.X < -100.0f)
	{
		Death();
	}
}

void DogFish::DeathStart()
{
	ChangeAnimation("Death");
	BodyCollision->Off();
	CreateDeathEffect();
}

void DogFish::DeathUpdate(float _Delta)
{
	float4 MovePos = float4::UP * Speed * _Delta;
	Transform.AddLocalPosition(MovePos);

	float4 Pos = Transform.GetWorldPosition();
	if (Pos.Y > 0.0f)
	{
		Death();
	}
}