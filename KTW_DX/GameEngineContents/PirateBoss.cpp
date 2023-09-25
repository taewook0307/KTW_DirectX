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
	PirateRenderer->CreateAnimation("PirateShoot", "Pirate_Shoot");
	PirateRenderer->SetEndEvent("PirateShoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("PirateIdle");
		}
	);
	PirateRenderer->ChangeAnimation("PirateIdle");
	PirateRenderer->AutoSpriteSizeOn();
	PirateRenderer->SetPivotType(PivotType::Bottom);
}

void PirateBoss::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		PirateRenderer->ChangeAnimation("PirateShoot");
	}
}