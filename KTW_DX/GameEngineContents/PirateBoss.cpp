#include "PreCompile.h"
#include "PirateBoss.h"

PirateBoss::PirateBoss()
{
}

PirateBoss::~PirateBoss()
{
}

void PirateBoss::Start()
{
	PirateRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	PirateRenderer->CreateAnimation("PirateIdle", "Pirate_Idle");
	PirateRenderer->CreateAnimation("PirateLaugh", "Pirate_Laugh");
	PirateRenderer->CreateAnimation("PirateShootReady", "Pirate_Shoot_Ready", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("PirateShootReady",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("PirateShootIdle");
		}
	);
	PirateRenderer->CreateAnimation("PirateShootIdle", "Pirate_Shoot_Idle", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("PirateShootIdle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("PirateShoot");
		}
	);
	PirateRenderer->CreateAnimation("PirateShoot", "Pirate_Shoot", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("PirateShoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("PirateShootEnd");
		}
	);
	PirateRenderer->CreateAnimation("PirateShootEnd", "Pirate_Shoot_End", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("PirateShootEnd",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("PirateIdle");
		}
	);
	PirateRenderer->ChangeAnimation("PirateIdle");
	PirateRenderer->AutoSpriteSizeOn();
	PirateRenderer->SetPivotType(PivotType::Bottom);

	/*PirateUpperRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BossEffect);
	PirateUpperRenderer->CreateAnimation("PirateShootUpper", "Pirate_Shoot_Upper");
	PirateUpperRenderer->AutoSpriteSizeOn();
	PirateUpperRenderer->SetPivotType(PivotType::Bottom);
	PirateUpperRenderer->Off();*/
}

void PirateBoss::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		PirateRenderer->ChangeAnimation("PirateShootReady");
		//PirateUpperRenderer->On();
		//PirateUpperRenderer->ChangeAnimation("PirateShootUpper");
	}

	if (true == GameEngineInput::IsDown('O'))
	{
		PirateRenderer->ChangeAnimation("PirateLaugh");
	}
}