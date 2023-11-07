#include "PreCompile.h"
#include "Summon_Fire.h"

#include "BaseCharacter.h"

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

	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent) { DirPosSetting(); };
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

	FireRenderer->CreateAnimation("Fire_Death", "DevilAttacker_Death", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				FireCollision->Off();
				FireRenderer->ChangeAnimation("Fire_Death");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == FireRenderer->IsCurAnimationEnd())
				{
					Death();
				}
			};
		FireState.CreateState(ESUMMONATTACKOBJECTSTATE::Death, Para);
	}

	FireRenderer->AutoSpriteSizeOn();

	FireCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	FireCollision->Transform.SetLocalScale(FIRECOLLISIONSCALE);

	FireState.ChangeState(ESUMMONATTACKOBJECTSTATE::Spawn);
}

void Summon_Fire::Update(float _Delta)
{
	FireState.Update(_Delta);
}

void Summon_Fire::DirPosSetting()
{
	float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	float4 Pos = Transform.GetWorldPosition();

	float4 Dir = CharacterPos - Pos;

	DirPos = Dir.NormalizeReturn();
}

void Summon_Fire::ChangeStateReq()
{
	FireState.ChangeState(ESUMMONATTACKOBJECTSTATE::Move);
}