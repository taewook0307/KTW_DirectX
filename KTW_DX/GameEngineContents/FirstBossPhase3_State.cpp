#include "PreCompile.h"
#include "FirstBossPhase3.h"

#include "Map.h"

void FirstBossPhase3::IntroStart()
{
	ChangeAnimation("Intro");
	FirstBossRenderer->AnimationPauseOn();
}

void FirstBossPhase3::IntroUpdate(float _Delta)
{
	if (IntroTimer < 0.0f)
	{
		ChangeState(FirstBossState::Idle);
		return;
	}

	GameEngineColor CurColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == CurColor)
	{
		FirstBossRenderer->AnimationPauseOff();
		GravityReset();
		IntroTimer -= _Delta;
	}
	else
	{
		GravityOn(_Delta);
	}
}

void FirstBossPhase3::IdleStart()
{
	ChangeAnimation("Idle");
}

void FirstBossPhase3::IdleUpdate(float _Delta)
{

}

void FirstBossPhase3::MoveStart()
{
	ChangeAnimation("Move");
}

void FirstBossPhase3::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (ActorDir::Left == FirstBossDir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = { -60.0f, 70.0f };
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = { 60.0f, 70.0f };
	}

	CheckPos += Transform.GetWorldPosition();

	GameEngineColor CheckColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

	if (FLOORCOLOR == CheckColor)
	{
		ChangeState(FirstBossState::Turn);
		return;
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
	}
}

void FirstBossPhase3::TurnStart()
{
	ChangeAnimation("Turn");
}

void FirstBossPhase3::TurnUpdate(float _Delta)
{
	if (true == FirstBossRenderer->IsCurAnimationEnd())
	{
		DirChange();
		ChangeState(FirstBossState::Move);
		return;
	}
}

void FirstBossPhase3::AttackStart()
{
	ChangeAnimation("Attack");
}

void FirstBossPhase3::AttackUpdate(float _Delta)
{

}

void FirstBossPhase3::DeathStart()
{
	ChangeAnimation("Death");
}

void FirstBossPhase3::DeathUpdate(float _Delta)
{

}