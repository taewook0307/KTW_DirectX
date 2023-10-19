#include "PreCompile.h"
#include "FirstBoss.h"

#include "Map.h"
#include "FirstBossMoveDust.h"

void FirstBoss::FirstBossMove(float4 _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	float4 CurPos = Transform.GetWorldPosition();

	if (EACTORDIR::Left == FirstBossDir)
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

void FirstBoss::CreateMoveDust()
{
	std::shared_ptr<FirstBossMoveDust> MoveEffect = GetLevel()->CreateActor<FirstBossMoveDust>(EUPDATEORDER::Effect);
	float4 MonsterPos = Transform.GetWorldPosition();
	MoveEffect->Transform.SetLocalPosition(MonsterPos);

	if (EBOSSPHASE::Phase2 == CurPhase)
	{
		MoveEffect->ChangeEffectPhase2();
	}
}

void FirstBoss::IntroStart()
{
	IsIntroState = true;
	ChangeAnimation("Intro");
}

void FirstBoss::IntroUpdate(float _Delta)
{
	ActorGravity(_Delta, Transform.GetWorldPosition());

	if (true == FirstBossRenderer->IsCurAnimation("FirstBoss_Phase2_IntroStay"))
	{
		Phase2IntroTimer -= _Delta;
	}

	if (Phase2IntroTimer < 0.0f && true == FirstBossRenderer->IsCurAnimationEnd() && true == FirstBossRenderer->IsCurAnimation("FirstBoss_Phase2_IntroStay"))
	{
		FirstBossRenderer->ChangeAnimation("FirstBoss_Phase2_IntroEnd");
		Phase2IntroTimer = 0.0f;
	}
}

void FirstBoss::IdleStart()
{
	if (EBOSSPHASE::Phase2 == CurPhase)
	{
		float4 CollisionScale = PHASE2BODYCOLLISIONSCALE;
		float4 CollisionPosition = { 0.0f, CollisionScale.Half().Y };

		FirstBossCollision->Transform.SetLocalScale(CollisionScale);
		FirstBossCollision->Transform.SetLocalPosition(CollisionPosition);
	}
	ChangeAnimation("Idle");
}

void FirstBoss::IdleUpdate(float _Delta)
{
	float4 BossPos = Transform.GetWorldPosition();
	ActorGravity(_Delta, BossPos);

	if (true == FirstBossRenderer->IsCurAnimationEnd())
	{
		ChangeState(EBOSSSTATE::Move);
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
		ActorGravity(_Delta, Transform.GetWorldPosition() + float4{ 0.0f, 80.0f });
	}
	else
	{
		ActorGravity(_Delta, Transform.GetWorldPosition());
	}

	float GravityY = GetGravityForce().Y;

	if (GravityY < 50.0f && GravityY > 0.0f)
	{
		if (EBOSSPHASE::Phase1 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("FirstBoss_Phase1_MoveStay"))
		{
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase1_MoveStay");
		}
		else if (EBOSSPHASE::Phase2 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("FirstBoss_Phase2_MoveStay"))
		{
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase2_MoveStay");
		}
		return;
	}

	if (GravityY < 0.0f)
	{
		if (EBOSSPHASE::Phase1 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("FirstBoss_Phase1_MoveEnd"))
		{
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase1_MoveEnd");
		}
		else if (EBOSSPHASE::Phase2 == CurPhase
			&& false == FirstBossRenderer->IsCurAnimation("FirstBoss_Phase2_MoveEnd"))
		{
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase2_MoveEnd");
		}
		return;
	}

	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == Color)
	{
		++BounceCount;
		CreateMoveDust();
		ChangeState(EBOSSSTATE::Idle);
		return;
	}
}

void FirstBoss::AttackStart()
{
	ChangeAnimation("Attack");
	DirCheckPrevAttack();
}

void FirstBoss::AttackUpdate(float _Delta)
{
	ActorGravity(_Delta, Transform.GetWorldPosition());
}

void FirstBoss::DeathStart()
{
	ChangeAnimation("Death");
	Phase2End = true;
}

void FirstBoss::DeathUpdate(float _Delta)
{
	ActorGravity(_Delta, Transform.GetWorldPosition());

	if (true == FirstBossCollision->Collision(ECOLLISIONORDER::UnDamageBoss))
	{
		ChangeState(EBOSSSTATE::Slime);
		return;
	}
}

void FirstBoss::SlimeStart()
{
	ChangeAnimation("Slime");
	FirstBossCollision->Off();
}

void FirstBoss::SlimeUpdate(float _Delta)
{

}