#include "PreCompile.h"
#include "FirstBossPhase3.h"

#include "Map.h"

void FirstBossPhase3::IntroStart()
{
	ChangeAnimation("Intro");
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

}

void FirstBossPhase3::TurnStart()
{
	ChangeAnimation("Turn");
}

void FirstBossPhase3::TurnUpdate(float _Delta)
{

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