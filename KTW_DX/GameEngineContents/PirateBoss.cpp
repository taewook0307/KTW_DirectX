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
	PirateRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Boss);
	PirateRenderer->CreateAnimation("PirateIdle", "Pirate_Idle", 1.0f);
	PirateRenderer->CreateAnimation("PirateShoot", "Pirate_Shoot", 1.0f);
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