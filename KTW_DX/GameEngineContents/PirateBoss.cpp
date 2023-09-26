#include "PreCompile.h"
#include "PirateBoss.h"

#include "PirateBullet.h"

PirateBoss::PirateBoss()
{
}

PirateBoss::~PirateBoss()
{
}

void PirateBoss::Start()
{
	// PirateUpperRenderer
	PirateUpperRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BossEffect);
	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_Upper", "Pirate_Shoot_Upper");
	PirateUpperRenderer->SetEndEvent("Pirate_Shoot_Upper",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->Off();
		}
	);

	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_Ready_Upper", "Pirate_Shoot_Ready_Upper");
	PirateUpperRenderer->SetEndEvent("Pirate_Shoot_Ready_Upper",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->Off();
		}
	);

	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_Idle_Upper", "Pirate_Shoot_Idle_Upper");
	PirateUpperRenderer->SetEndEvent("Pirate_Shoot_Idle_Upper",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->Off();
		}
	);

	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_End_Upper", "Pirate_Shoot_End_Upper");
	PirateUpperRenderer->SetEndEvent("Pirate_Shoot_End_Upper",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->Off();
		}
	);

	PirateUpperRenderer->AutoSpriteSizeOn();
	PirateUpperRenderer->SetPivotType(PivotType::Bottom);
	PirateUpperRenderer->Off();

	// Pirate
	PirateRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	PirateRenderer->CreateAnimation("Pirate_Idle", "Pirate_Idle");

	PirateRenderer->CreateAnimation("Pirate_Laugh", "Pirate_Laugh");

	PirateRenderer->CreateAnimation("Pirate_Knockout", "Pirate_Knockout");

	PirateRenderer->CreateAnimation("Pirate_Whistle", "Pirate_Whistle", 0.1f, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Whistle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Idle");
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Shoot_Ready", "Pirate_Shoot_Ready", 0.1f, -1, -1, false);
	PirateRenderer->SetFrameEvent("Pirate_Shoot_Ready", 16,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->On();
			PirateUpperRenderer->ChangeAnimation("Pirate_Shoot_Ready_Upper");
		}
	);
	PirateRenderer->SetEndEvent("Pirate_Shoot_Ready",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Shoot_Idle");
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Shoot_Idle", "Pirate_Shoot_Idle", 0.1f, -1, -1, false);
	PirateRenderer->SetStartEvent("Pirate_Shoot_Idle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->On();
			PirateUpperRenderer->ChangeAnimation("Pirate_Shoot_Idle_Upper");
		}
	);
	PirateRenderer->SetEndEvent("Pirate_Shoot_Idle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Shoot");
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Shoot", "Pirate_Shoot", 0.1f, -1, -1, false);
	PirateRenderer->SetStartEvent("Pirate_Shoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->On();
			PirateUpperRenderer->ChangeAnimation("Pirate_Shoot_Upper");
		}
	);
	PirateRenderer->SetEndEvent("Pirate_Shoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreatePirateBullet();
			PirateRenderer->ChangeAnimation("Pirate_Shoot_End");
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Shoot_End", "Pirate_Shoot_End", 0.1f, -1, -1, false);
	PirateRenderer->SetStartEvent("Pirate_Shoot_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->On();
			PirateUpperRenderer->ChangeAnimation("Pirate_Shoot_End_Upper");
		}
	);
	PirateRenderer->SetEndEvent("Pirate_Shoot_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Idle");
		}
	);
	PirateRenderer->ChangeAnimation("Pirate_Idle");
	PirateRenderer->AutoSpriteSizeOn();
	PirateRenderer->SetPivotType(PivotType::Bottom);
}

void PirateBoss::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		PirateRenderer->ChangeAnimation("Pirate_Shoot_Ready");
	}

	if (true == GameEngineInput::IsDown('O'))
	{
		PirateRenderer->ChangeAnimation("Pirate_Laugh");
	}

	if (true == GameEngineInput::IsDown('I'))
	{
		PirateRenderer->ChangeAnimation("Pirate_Whistle");
	}

	if (true == GameEngineInput::IsDown('U'))
	{
		PirateRenderer->ChangeAnimation("Pirate_Knockout");
	}
}

void PirateBoss::CreatePirateBullet()
{
	std::shared_ptr<PirateBullet> NewBullet = GetLevel()->CreateActor<PirateBullet>(EUPDATEORDER::Bullet);
	float4 PiratePos = Transform.GetWorldPosition();
	float4 BulletPos = { PiratePos.X, PiratePos.Y + 100.0f };
	NewBullet->Transform.SetLocalPosition(BulletPos);
	//NewBullet->SetDirVector()
}