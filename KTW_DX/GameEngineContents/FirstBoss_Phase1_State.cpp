#include "PreCompile.h"
#include "FirstBoss.h"

#include "Map.h"

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
	FirstBossRenderer->SetPivotType(PivotType::Bottom);
	ChangeAnimation("Idle");
}

void FirstBoss::IdleUpdate(float _Delta)
{
	BossGravity(float4::ZERO, _Delta);

	if (true == FirstBossRenderer->IsCurAnimationEnd())
	{
		ChangeState(FirstBossState::Move);
		return;
	}
}

void FirstBoss::MoveStart()
{
	ChangeAnimation("Move");
	SetGravityForce(float4::UP * JumpPower);
}

void FirstBoss::MoveUpdate(float _Delta)
{
	if (GetGravityForce().Y > 0)
	{
		BossGravity(Transform.GetWorldPosition() + float4{ 0.0f, 80.0f }, _Delta);
	}
	else
	{
		BossGravity(Transform.GetWorldPosition(), _Delta);
	}

	float GravityY = GetGravityForce().Y;

	if (GravityY < 50.0f && GravityY > 0.0f)
	{
		if (BossPhase::Phase1 == CurPhase)
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase1_MoveStay");
		}
		else if (BossPhase::Phase2 == CurPhase)
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase2_MoveStay");
		}
		return;
	}

	if (GravityY < 0.0f)
	{
		if (BossPhase::Phase1 == CurPhase)
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase1_MoveEnd");
		}
		else if (BossPhase::Phase2 == CurPhase)
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase2_MoveEnd");
		}
		return;
	}

	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == Color)
	{
		ChangeState(FirstBossState::Idle);
		return;
	}
}