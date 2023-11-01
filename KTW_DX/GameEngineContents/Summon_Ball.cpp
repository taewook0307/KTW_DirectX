#include "PreCompile.h"
#include "Summon_Ball.h"

Summon_Ball::Summon_Ball()
{
}

Summon_Ball::~Summon_Ball()
{
}

void Summon_Ball::Start()
{
	BallRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	BallRenderer->CreateAnimation("Ball_Spawn", "DevilAttacker_Spawn", 0.1f, -1, -1, false);
	BallRenderer->SetStartEvent("Ball_Spawn",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			float4 Pos = Transform.GetWorldPosition();
			CreateSummonEffect(Pos);
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { BallRenderer->ChangeAnimation("Ball_Spawn"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == BallRenderer->IsCurAnimationEnd())
				{
					BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Idle);
				}
			};
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Spawn, Para);
	}

	BallRenderer->CreateAnimation("FireBall_Idle", "FireBall_Idle");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { BallRenderer->ChangeAnimation("FireBall_Idle"); };
		BallState.CreateState(ESUMMONATTACKOBJECTSTATE::Idle, Para);
	}

	BallRenderer->AutoSpriteSizeOn();

	BallState.ChangeState(ESUMMONATTACKOBJECTSTATE::Spawn);
}

void Summon_Ball::Update(float _Delta)
{
	BallState.Update(_Delta);
}