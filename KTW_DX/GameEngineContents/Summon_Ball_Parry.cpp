#include "PreCompile.h"
#include "Summon_Ball_Parry.h"

Summon_Ball_Parry::Summon_Ball_Parry()
{
}

Summon_Ball_Parry::~Summon_Ball_Parry()
{
}

void Summon_Ball_Parry::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	Renderer->CreateAnimation("Ball_Parry_Spawn", "DevilAttackObject_Parry_Spawn", 0.1f, -1, -1, false);
	Renderer->SetStartEvent("Ball_Parry_Spawn",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			float4 Pos = Transform.GetWorldPosition();
			CreateSummonEffectParry(Pos);
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { Renderer->ChangeAnimation("Ball_Parry_Spawn"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Idle);
				}
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Spawn, Para);
	}

	Renderer->CreateAnimation("Ball_Parry_Idle", "FireBall_Parry_Idle");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { Renderer->ChangeAnimation("Ball_Parry_Idle"); };
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Idle, Para);
	}

	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { DirPosSetting(); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				BallMove(_DeltaTime);

				if (true == BallCollision->Collision(ECOLLISIONORDER::Player))
				{
					BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Death);
					return;
				}
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Move, Para);
	}

	Renderer->CreateAnimation("Ball_Parry_Death", "DevilAttackObject_Parry_Death", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				BallCollision->Off();
				Renderer->ChangeAnimation("Ball_Parry_Death");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					Death();
				}
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Death, Para);
	}

	Renderer->AutoSpriteSizeOn();

	BallCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	BallCollision->Transform.SetLocalScale(BALLCOLLISIONSCALE);

	ParryCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::ParryObject);
	ParryCollision->Transform.SetLocalScale(BALLCOLLISIONSCALE);

	BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Spawn);
}