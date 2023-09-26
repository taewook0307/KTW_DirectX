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
	PirateRenderer->CreateAnimation("Pirate_Idle", "Pirate_Idle");
	PirateRenderer->CreateAnimation("Pirate_Laugh", "Pirate_Laugh");
	PirateRenderer->CreateAnimation("Pirate_Whistle", "Pirate_Whistle", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Whistle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Idle");
		}
	);
	PirateRenderer->CreateAnimation("Pirate_Shoot_Ready", "Pirate_Shoot_Ready", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Shoot_Ready",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Shoot_Idle");
		}
	);
	PirateRenderer->CreateAnimation("Pirate_Shoot_Idle", "Pirate_Shoot_Idle", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Shoot_Idle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Shoot");
		}
	);
	PirateRenderer->CreateAnimation("Pirate_Shoot", "Pirate_Shoot", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Shoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Shoot_End");
		}
	);
	PirateRenderer->CreateAnimation("Pirate_Shoot_End", "Pirate_Shoot_End", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Shoot_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Idle");
		}
	);
	PirateRenderer->ChangeAnimation("Pirate_Idle");
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
		PirateRenderer->ChangeAnimation("Pirate_Shoot_Ready");
		//PirateUpperRenderer->On();
		//PirateUpperRenderer->ChangeAnimation("PirateShootUpper");
	}

	if (true == GameEngineInput::IsDown('O'))
	{
		PirateRenderer->ChangeAnimation("Pirate_Laugh");
	}

	if (true == GameEngineInput::IsDown('I'))
	{
		PirateRenderer->ChangeAnimation("Pirate_Whistle");
	}
}