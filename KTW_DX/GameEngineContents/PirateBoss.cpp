﻿#include "PreCompile.h"
#include "PirateBoss.h"

#include "PirateBullet.h"
#include "PirateBulletParry.h"
#include "Shark.h"
#include "Periscope.h"
#include "Whistle_Effect.h"
#include "ShipBoss.h"

PirateBoss* PirateBoss::MainPirateBoss = nullptr;

PirateBoss::PirateBoss()
{
	HitCount = 0;
	MainPirateBoss = this;
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
	PirateRenderer->SetFrameEvent("Pirate_Whistle", 21,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_pirate_foot.wav");
		}
	);

	PirateRenderer->SetFrameEvent("Pirate_Whistle", 24,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_pirate_whistle.wav");
			std::shared_ptr<Whistle_Effect> Effect = GetLevel()->CreateActor<Whistle_Effect>(EUPDATEORDER::Effect);
			float4 Pos = Transform.GetWorldPosition();
			float4 EffectPos = { Pos.X - 160.0f, Pos.Y + 390.0f };
			Effect->Transform.SetLocalPosition(EffectPos);
		}
	);

	PirateRenderer->SetEndEvent("Pirate_Whistle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SummonEnemy();
			PirateRenderer->ChangeAnimation("Pirate_Idle");
			return;
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Shoot_Ready", "Pirate_Shoot_Ready", PIRATEBOSSANIMATIONINTER, -1, -1, false);
	PirateRenderer->SetFrameEvent("Pirate_Shoot_Ready", 9,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_pirate_gun_start.wav");
		}
	);
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
			ShootSoundPlay();
			CreatePirateBullet();
		}
	);
	PirateRenderer->SetEndEvent("Pirate_Shoot",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			if (0 >= ShootCount)
			{
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
	PirateRenderer->SetFrameEvent("Pirate_Shoot_End", 7,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_pirate_gun_end.wav");
		}
	);
	PirateRenderer->SetEndEvent("Pirate_Shoot_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(EPIRATEBOSSSTATE::Idle);
			return;
		}
	);

	PirateRenderer->CreateAnimation("Pirate_Death", "Pirate_Death", PIRATEBOSSANIMATIONINTER);

	PirateRenderer->AutoSpriteSizeOn();
	PirateRenderer->SetPivotType(PivotType::Bottom);

	PirateCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossBody);
	PirateCollision->Transform.SetLocalScale(PIRATECOLLISIONSCALE);
	PirateCollision->Transform.SetLocalPosition(PIRATECOLLISIONPOSITION);

	ChangeState(EPIRATEBOSSSTATE::Intro);

	GameEngineInput::AddInputObject(this);
}

void PirateBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	PhaseChange();

	if (true == GameEngineInput::IsDown('1', this))
	{
		if (EBOSSPHASE::Phase2 != CurPhase)
		{
			CurPhase = EBOSSPHASE::Phase2;
			ShipBoss::MainShip->CurPhase = EBOSSPHASE::Phase2;
		}

		ChangeState(EPIRATEBOSSSTATE::Whistle);
		return;
	}
}

void PirateBoss::ChangeState(EPIRATEBOSSSTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
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
		case EPIRATEBOSSSTATE::Death:
			DeathStart();
			break;
		default:
			break;
		}

		CurState = _CurState;
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
	case EPIRATEBOSSSTATE::Whistle:
		return WhistleUpdate(_Delta);
	case EPIRATEBOSSSTATE::Death:
		return DeathUpdate(_Delta);
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
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);
	int BulletType = Random.RandomInt(0, 1);

	std::shared_ptr<PirateBullet> NewBullet = nullptr;

	if (0 == BulletType)
	{
		NewBullet = GetLevel()->CreateActor<PirateBullet>(EUPDATEORDER::Bullet);
	}
	else
	{
		NewBullet = GetLevel()->CreateActor<PirateBulletParry>(EUPDATEORDER::Bullet);
	}
	
	if (nullptr == NewBullet)
	{
		MsgBoxAssert("해적 보스가 총알 생성에 실패했습니다.");
		return;
	}

	float4 PiratePos = Transform.GetWorldPosition();
	float4 BulletPos = { PiratePos.X - 220.0f, PiratePos.Y + 120.0f };

	NewBullet->Transform.SetLocalPosition(BulletPos);

	--ShootCount;
}

void PirateBoss::PhaseChange()
{
	if (PHASE1HP < HitCount && EBOSSPHASE::Phase1 == CurPhase)
	{
		CurPhase = EBOSSPHASE::Phase2;
		ShipBoss::MainShip->CurPhase = EBOSSPHASE::Phase2;
		return;
	}

	if (PHASE2HP < HitCount && EBOSSPHASE::Phase2 == CurPhase)
	{
		CurPhase = EBOSSPHASE::Phase3;
		ShipBoss::MainShip->CurPhase = EBOSSPHASE::Phase3;
		HitCount = 0;
		return;
	}
}

void PirateBoss::SummonEnemy()
{
	SummonActors.clear();

	SummonActors.resize(1);

	if (false == SummonScope)
	{
		SummonActors[0] = GetLevel()->CreateActor<Shark>(EUPDATEORDER::Monster);
		SummonActors[0]->Transform.SetLocalPosition(SUMMONSHARKPOS);
		SummonScope = true;
	}
	else
	{
		SummonActors[0] = GetLevel()->CreateActor<Periscope>(EUPDATEORDER::Monster);
		SummonActors[0]->Transform.SetLocalPosition(SUMMONSCOPEPOS);
		SummonScope = false;
	}
}

void PirateBoss::ChangePhase3()
{
	ChangeState(EPIRATEBOSSSTATE::Death);
	return;
}