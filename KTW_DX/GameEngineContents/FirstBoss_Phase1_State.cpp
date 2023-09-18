#include "PreCompile.h"
#include "FirstBoss.h"

void FirstBoss::IntroStart()
{
	ChangeAnimation("Intro");
}

void FirstBoss::IntroUpdate(float _Delta)
{
	if (true == FirstBossRenderer->IsCurAnimationEnd())
	{
		ChangeState(FirstBossState::Idle);
		return;
	}
}

void FirstBoss::IdleStart()
{
	ChangeAnimation("Idle");
}

void FirstBoss::IdleUpdate(float _Delta)
{

}

void FirstBoss::MoveStart()
{
	ChangeAnimation("Move");
}

void FirstBoss::MoveUpdate(float _Delta)
{

}