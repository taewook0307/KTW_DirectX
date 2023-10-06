#include "PreCompile.h"
#include "Barrel.h"

#include "BaseCharacter.h"
#include "Map.h"

void Barrel::IdleStart()
{
	ChangeAnimation("Idle");
	AttackCollision->Off();
}
void Barrel::IdleUpdate(float _Delta)
{
	if (IdleTimer < 0.0f)
	{
		IdleTimer = IDLETIMER;
		ChangeState(EBARRELSTATE::SmashReady);
		return;
	}

	BarrelMove(_Delta);

	IdleTimer -= _Delta;
}

void Barrel::SmashReadyStart()
{
	ChangeAnimation("SmashReady");
	AttackCollision->On();
}
void Barrel::SmashReadyUpdate(float _Delta)
{
	float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	float4 BarrelPos = Transform.GetWorldPosition();

	BarrelMove(_Delta);

	float Distance = fabs(CharacterPos.X - BarrelPos.X);

	if (Distance < 10.0f)
	{
		ChangeState(EBARRELSTATE::Drop);
		return;
	}
}

void Barrel::DropStart()
{
	ChangeAnimation("Drop");
}
void Barrel::DropUpdate(float _Delta)
{
	float4 BarrelPos = Transform.GetWorldPosition();
	GameEngineColor CheckColor = Map::MainMap->GetColor(BarrelPos, FLOORCOLOR);

	if (FLOORCOLOR != CheckColor)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(EBARRELSTATE::Smash);
		return;
	}
}

void Barrel::SmashStart()
{
	ChangeAnimation("Smash");
}
void Barrel::SmashUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		AttackCollision->Off();
		ChangeState(EBARRELSTATE::SmashEnd);
		return;
	}
}

void Barrel::SmashEndStart()
{
	ChangeAnimation("SmashEnd");
}
void Barrel::SmashEndUpdate(float _Delta)
{
	Transform.AddLocalPosition(float4::UP * 300.0f * _Delta);

	float4 BarrelPos = Transform.GetWorldPosition();

	if (-220.0f < BarrelPos.Y)
	{
		ChangeState(EBARRELSTATE::Idle);
		return;
	}
}