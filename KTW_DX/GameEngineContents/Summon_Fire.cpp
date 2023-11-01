#include "PreCompile.h"
#include "Summon_Fire.h"

Summon_Fire::Summon_Fire()
{
}

Summon_Fire::~Summon_Fire()
{
}

void Summon_Fire::Start()
{
	FireRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	FireRenderer->CreateAnimation("Fire_Spawn", "DevilAttacker_Spawn", 0.1f, -1, -1, false);
	FireRenderer->SetStartEvent("Fire_Spawn",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			float4 Pos = Transform.GetWorldPosition();
			CreateSummonEffect(Pos);
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { FireRenderer->ChangeAnimation("Fire_Spawn"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == FireRenderer->IsCurAnimationEnd())
				{
					FireState.ChangeState(ESUMMONATTACKOBJECTSTATE::Idle);
					return;
				}
			};
		FireState.CreateState(ESUMMONATTACKOBJECTSTATE::Spawn, Para);
	}

	FireRenderer->CreateAnimation("Fire_Idle", "Fire_Idle");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { FireRenderer->ChangeAnimation("Fire_Idle"); };
		FireState.CreateState(ESUMMONATTACKOBJECTSTATE::Idle, Para);
	}
	FireRenderer->AutoSpriteSizeOn();

	FireState.ChangeState(ESUMMONATTACKOBJECTSTATE::Spawn);
}

void Summon_Fire::Update(float _Delta)
{
	FireState.Update(_Delta);
}