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
	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_Upper", "Pirate_Shoot_Upper", PIRATEBOSSANIMATIONINTER, -1, -1, false);
	PirateUpperRenderer->SetEndEvent("Pirate_Shoot_Upper",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->Off();
		}
	);

	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_Ready_Upper", "Pirate_Shoot_Ready_Upper", PIRATEBOSSANIMATIONINTER, -1, -1, false);
	PirateUpperRenderer->SetEndEvent("Pirate_Shoot_Ready_Upper",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->Off();
		}
	);

	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_Idle_Upper", "Pirate_Shoot_Idle_Upper", PIRATEBOSSANIMATIONINTER, -1, -1, false);
	PirateUpperRenderer->SetEndEvent("Pirate_Shoot_Idle_Upper",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->Off();
		}
	);

	PirateUpperRenderer->CreateAnimation("Pirate_Shoot_End_Upper", "Pirate_Shoot_End_Upper", PIRATEBOSSANIMATIONINTER, -1, -1, false);
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
	PirateRenderer->SetEndEvent("Pirate_Laugh",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(EPIRATEBOSSSTATE::Idle);
			return;
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Knockout", "Pirate_Knockout", PIRATEBOSSANIMATIONINTER, -1, -1, false);

	PirateRenderer->CreateAnimation("Pirate_Whistle", "Pirate_Whistle", PIRATEBOSSANIMATIONINTER, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Whistle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(EPIRATEBOSSSTATE::Idle);
			return;
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Shoot_Ready", "Pirate_Shoot_Ready", PIRATEBOSSANIMATIONINTER, -1, -1, false);
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

	PirateRenderer->CreateAnimation("Pirate_Shoot_Idle", "Pirate_Shoot_Idle", PIRATEBOSSANIMATIONINTER, -1, -1, false);
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

	PirateRenderer->CreateAnimation("Pirate_Shoot", "Pirate_Shoot", PIRATEBOSSANIMATIONINTER, -1, -1, false);
	PirateRenderer->SetStartEvent("Pirate_Shoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateUpperRenderer->On();
			PirateUpperRenderer->ChangeAnimation("Pirate_Shoot_Upper");
		}
	);
	PirateRenderer->SetFrameEvent("Pirate_Shoot", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreatePirateBullet();
		}
	);
	PirateRenderer->SetEndEvent("Pirate_Shoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			if (2 < ShootCount)
			{
				ShootCount = 0;
				PirateRenderer->ChangeAnimation("Pirate_Shoot_End");
			}
			else
			{
				PirateRenderer->ChangeAnimation("Pirate_Shoot_Idle");
			}
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Shoot_End", "Pirate_Shoot_End", PIRATEBOSSANIMATIONINTER, -1, -1, false);
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
			ChangeState(EPIRATEBOSSSTATE::Idle);
			return;
		}
	);
	PirateRenderer->AutoSpriteSizeOn();
	PirateRenderer->SetPivotType(PivotType::Bottom);

	ChangeState(EPIRATEBOSSSTATE::Idle);
}

void PirateBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('O'))
	{
		ChangeState(EPIRATEBOSSSTATE::Shoot);
		return;
	}
	if (true == GameEngineInput::IsDown('I'))
	{
		ChangeState(EPIRATEBOSSSTATE::Knockout);
		return;
	}
	if (true == GameEngineInput::IsDown('O'))
	{
		ChangeState(EPIRATEBOSSSTATE::Shoot);
		return;
	}
}

void PirateBoss::ChangeState(EPIRATEBOSSSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case EPIRATEBOSSSTATE::Idle:
			IdleStart();
			break;
		case EPIRATEBOSSSTATE::Shoot:
			ShootStart();
			break;
		case EPIRATEBOSSSTATE::Laugh:
			LaughStart();
			break;
		case EPIRATEBOSSSTATE::Knockout:
			KnockoutStart();
			break;
		case EPIRATEBOSSSTATE::Whistle:
			WhistleStart();
			break;
		default:
			break;
		}

		CurState = _State;
	}
}

void PirateBoss::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case EPIRATEBOSSSTATE::Idle:
		return IdleUpdate(_Delta);
	case EPIRATEBOSSSTATE::Shoot:
		return ShootUpdate(_Delta);
	case EPIRATEBOSSSTATE::Laugh:
		return LaughUpdate(_Delta);
	case EPIRATEBOSSSTATE::Knockout:
		return KnockoutUpdate(_Delta);
	case EPIRATEBOSSSTATE::Whistle:
		return WhistleUpdate(_Delta);
	default:
		break;
	}
}

void PirateBoss::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Pirate_";

	AnimationName += _State;

	if ("Shoot" == _State)
	{
		AnimationName += "_Ready";
	}

	State = _State;

	PirateRenderer->ChangeAnimation(AnimationName);
}

void PirateBoss::CreatePirateBullet()
{
	std::shared_ptr<PirateBullet> NewBullet = GetLevel()->CreateActor<PirateBullet>(EUPDATEORDER::Bullet);
	
	if (nullptr == NewBullet)
	{
		MsgBoxAssert("해적 보스가 총알 생성에 실패했습니다.");
		return;
	}

	float4 PiratePos = Transform.GetWorldPosition();
	float4 BulletPos = { PiratePos.X - 220.0f, PiratePos.Y + 120.0f };

	NewBullet->Transform.SetLocalPosition(BulletPos);

	++ShootCount;
}