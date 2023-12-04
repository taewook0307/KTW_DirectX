#include "PreCompile.h"
#include "Summon_Fire_Parry.h"

Summon_Fire_Parry::Summon_Fire_Parry()
{
}

Summon_Fire_Parry::~Summon_Fire_Parry()
{
}

void Summon_Fire_Parry::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	Renderer->CreateAnimation("Fire_Parry_Spawn", "DevilAttackObject_Parry_Spawn", 0.1f, -1, -1, false);
	Renderer->SetStartEvent("Fire_Parry_Spawn",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			float4 Pos = Transform.GetWorldPosition();
			CreateSummonEffectParry(Pos);
		}
	);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent) { Renderer->ChangeAnimation("Fire_Parry_Spawn"); };
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					FireState.ChangeState(ESUMMONATTACKOBJECTSTATE::Idle);
					return;
				}
			};
		FireState.CreateState(ESUMMONATTACKOBJECTSTATE::Spawn, Para);
	}

	Renderer->CreateAnimation("Fire_Parry_Idle", "Fire_Parry_Idle");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { Renderer->ChangeAnimation("Fire_Parry_Idle"); };
		FireState.CreateState(ESUMMONATTACKOBJECTSTATE::Idle, Para);
	}

	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				AttackSoundPlay();
				DirPosSetting();
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == CameraOutCheck())
				{
					Death();
					return;
				}

				if (float4::ZERO != DirPos)
				{
					Transform.AddLocalPosition(DirPos * _DeltaTime * Speed);
				}

				if (true == FireCollision->Collision(ECOLLISIONORDER::Player))
				{
					FireState.ChangeState(ESUMMONATTACKOBJECTSTATE::Death);
					return;
				}
			};
		FireState.CreateState(ESUMMONATTACKOBJECTSTATE::Move, Para);
	}

	Renderer->CreateAnimation("Fire_Parry_Death", "DevilAttackObject_Parry_Death", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				FireCollision->Off();
				Renderer->ChangeAnimation("Fire_Parry_Death");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					Death();
				}
			};
		FireState.CreateState(ESUMMONATTACKOBJECTSTATE::Death, Para);
	}

	Renderer->AutoSpriteSizeOn();

	FireCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	FireCollision->Transform.SetLocalScale(FIRECOLLISIONSCALE);

	ParryCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::ParryObject);
	ParryCollision->Transform.SetLocalScale(FIRECOLLISIONSCALE);

	FireState.ChangeState(ESUMMONATTACKOBJECTSTATE::Spawn);
}