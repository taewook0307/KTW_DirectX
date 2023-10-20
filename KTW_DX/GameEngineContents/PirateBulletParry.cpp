#include "PreCompile.h"
#include "PirateBulletParry.h"

#include "BaseCharacter.h"

PirateBulletParry::PirateBulletParry()
{
}

PirateBulletParry::~PirateBulletParry()
{
}

void PirateBulletParry::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PrevBoss5);
	Renderer->CreateAnimation("Pirate_Bullet_Pink_Move", "Pirate_Bullet_Pink_Move");
	Renderer->CreateAnimation("Pirate_Bullet_Pink_Death", "Pirate_Bullet_Pink_Death");

	{
		CreateStateParameter Para;

		Para.Start =
			[=](GameEngineState* _State)
			{
				Renderer->ChangeAnimation("Pirate_Bullet_Pink_Move");
			};

		Para.Stay =
			[=](float _Delta, GameEngineState* _State)
			{
				HitCheck();
				PirateMove(_Delta);
				CameraOutCheck();
			};

		PirateBulletState.CreateState(EPIRATEBULLETSTATE::Move, Para);
	}

	{
		CreateStateParameter Para;

		Para.Start =
			[=](GameEngineState* _State)
			{
				BulletCollision->Off();
				Renderer->ChangeAnimation("Pirate_Bullet_Pink_Death");
			};

		Para.Stay =
			[=](float _Delta, GameEngineState* _State)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					Death();
				}
			};

		PirateBulletState.CreateState(EPIRATEBULLETSTATE::Death, Para);
	}

	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Left);

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	BulletCollision->Transform.SetLocalScale(PIRATEBULLETCOLLISIONSCALE);
	BulletCollision->Transform.SetLocalPosition(PIRATEBULLETCOLLISIONPOSITION);

	ParryCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::ParryObject);
	ParryCollision->Transform.SetLocalScale(PIRATEBULLETCOLLISIONSCALE);
	ParryCollision->Transform.SetLocalPosition(PIRATEBULLETCOLLISIONPOSITION);

	float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	PlayerPos = { CharacterPos.X, CharacterPos.Y + ADJUSTVALUE };
	PirateBulletState.ChangeState(EPIRATEBULLETSTATE::Move);
}

void PirateBulletParry::Update(float _Delta)
{
	PirateBulletState.Update(_Delta);
}

void PirateBulletParry::HitCheck()
{
	if (false == ParryActivation)
	{
		BulletCollision->Off();
		PirateBulletState.ChangeState(EPIRATEBULLETSTATE::Death);
		return;
	}
	else
	{
		if (true == BulletCollision->Collision(ECOLLISIONORDER::Player))
		{
			PirateBulletState.ChangeState(EPIRATEBULLETSTATE::Death);
			return;
		}
	}
}