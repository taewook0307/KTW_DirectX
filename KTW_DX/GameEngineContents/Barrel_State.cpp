#include "PreCompile.h"
#include "Barrel.h"

#include "BaseCharacter.h"

void Barrel::IdleStart()
{
	ChangeAnimation("Idle");
}
void Barrel::IdleUpdate(float _Delta)
{
	if (IdleTimer < 0.0f)
	{
		IdleTimer = IDLETIMER;
		ChangeState(EBARRELSTATE::SmashReady);
		return;
	}

	IdleTimer -= _Delta;
}

void Barrel::SmashReadyStart()
{
	ChangeAnimation("SmashReady");
}
void Barrel::SmashReadyUpdate(float _Delta)
{
	float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	float4 BarrelPos = Transform.GetWorldPosition();

	float Dir = fabs(CharacterPos.X - BarrelPos.X);

	if (Dir < 5.0f)
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
	if (true == Renderer->IsCurAnimationEnd())
	{
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
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(EBARRELSTATE::Idle);
		return;
	}
}