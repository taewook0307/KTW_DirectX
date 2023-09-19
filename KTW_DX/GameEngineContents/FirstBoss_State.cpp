#include "PreCompile.h"
#include "FirstBoss.h"

#include "Map.h"

void FirstBoss::FirstBossMove(float4 _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	float4 CurPos = Transform.GetWorldPosition();

	if (ActorDir::Left == FirstBossDir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = CurPos + float4{ -40.0f, 30.0f };
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = CurPos + float4{ 40.0f, 30.0f };
	}

	GameEngineColor Color = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

	if (FLOORCOLOR == Color)
	{
		DirChange();
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
	}
}


void FirstBoss::IntroStart()
{
	ChangeAnimation("Intro");
}

void FirstBoss::IntroUpdate(float _Delta)
{

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
	FirstBossMove(_Delta);

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
		if (BossPhase::Phase1 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("Boss_Phase1_MoveStay"))
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase1_MoveStay");
		}
		else if (BossPhase::Phase2 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("Boss_Phase2_MoveStay"))
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase2_MoveStay");
		}
		return;
	}

	if (GravityY < 0.0f)
	{
		if (BossPhase::Phase1 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("Boss_Phase1_MoveEnd"))
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase1_MoveEnd");
		}
		else if (BossPhase::Phase2 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("Boss_Phase2_MoveEnd"))
		{
			FirstBossRenderer->ChangeAnimation("Boss_Phase2_MoveEnd");
		}
		return;
	}

	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == Color)
	{
		++BounceCount;
		ChangeState(FirstBossState::Idle);
		return;
	}
}

void FirstBoss::AttackStart()
{
	ChangeAnimation("Attack");
}

void FirstBoss::AttackUpdate(float _Delta)
{
	BossGravity(Transform.GetWorldPosition(), _Delta);
}

void FirstBoss::DeathStart()
{
	ChangeAnimation("Death");
	Phase2End = true;
}

void FirstBoss::DeathUpdate(float _Delta)
{
	BossGravity(Transform.GetWorldPosition(), _Delta);

	if (true == FirstBossCollision->Collision(CollisionOrder::Monster))
	{
		ChangeState(FirstBossState::Slime);
		return;
	}
}

void FirstBoss::SlimeStart()
{
	ChangeAnimation("Slime");
}

void FirstBoss::SlimeUpdate(float _Delta)
{

}