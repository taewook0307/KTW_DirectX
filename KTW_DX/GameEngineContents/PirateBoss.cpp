#include "PreCompile.h"
#include "PirateBoss.h"

#include "PirateBullet.h"
#include "Shark.h"

PirateBoss::PirateBoss()
{
	HitCount = 0;
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

	PirateRenderer->CreateAnimation("Pirate_Intro_Ready", "Pirate_Intro", 0.1f, 0, 3, false);
	PirateRenderer->SetEndEvent("Pirate_Intro_Ready",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateRenderer->ChangeAnimation("Pirate_Intro");
		}
	);
	PirateRenderer->CreateAnimation("Pirate_Intro", "Pirate_Intro", PIRATEBOSSANIMATIONINTER, 4, 11, true);
	PirateRenderer->CreateAnimation("Pirate_Intro_End", "Pirate_Intro", PIRATEBOSSANIMATIONINTER, 12, 13, false);
	PirateRenderer->SetEndEvent("Pirate_Intro_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			IsIntroState = false;
			ChangeState(EPIRATEBOSSSTATE::Idle);
			return;
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Knockout", "Pirate_Knockout", PIRATEBOSSANIMATIONINTER, -1, -1, false);

	PirateRenderer->CreateAnimation("Pirate_Whistle", "Pirate_Whistle", PIRATEBOSSANIMATIONINTER, -1, -1, false);
	PirateRenderer->SetEndEvent("Pirate_Whistle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SummonEnemy();
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

	PirateCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossBody);
	PirateCollision->Transform.SetLocalScale(PIRATECOLLISIONSCALE);
	PirateCollision->Transform.SetLocalPosition(PIRATECOLLISIONPOSITION);

	ChangeState(EPIRATEBOSSSTATE::Intro);
}

void PirateBoss::Update(float _Delta)
{
	OutputDebugStringA(std::to_string(HitCount).c_str());
	OutputDebugStringA("\n");

	StateUpdate(_Delta);

	PhaseChange();
}

void PirateBoss::ChangeState(EPIRATEBOSSSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case EPIRATEBOSSSTATE::Intro:
			IntroStart();
			break;
		case EPIRATEBOSSSTATE::Idle:
			IdleStart();
			break;
		case EPIRATEBOSSSTATE::Shoot:
			ShootStart();
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
	case EPIRATEBOSSSTATE::Intro:
		return IntroUpdate(_Delta);
	case EPIRATEBOSSSTATE::Idle:
		return IdleUpdate(_Delta);
	case EPIRATEBOSSSTATE::Shoot:
		return ShootUpdate(_Delta);
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

void PirateBoss::PhaseChange()
{
	if (400 < HitCount && EBOSSPHASE::Phase1 == CurPhase)
	{
		CurPhase = EBOSSPHASE::Phase2;
		return;
	}

	if (952 < HitCount && EBOSSPHASE::Phase2 == CurPhase)
	{
		CurPhase = EBOSSPHASE::Phase3;
		HitCount = 0;
		return;
	}
}

void PirateBoss::SummonEnemy()
{
	std::shared_ptr SummonShark = GetLevel()->CreateActor<Shark>(EUPDATEORDER::Monster);
	SummonShark->Transform.SetLocalPosition({ 1000.0f, -500.0f });
}