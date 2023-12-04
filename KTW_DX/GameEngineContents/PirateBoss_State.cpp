#include "PreCompile.h"
#include "PirateBoss.h"

#include "Map.h"

void PirateBoss::IntroStart()
{
	IsIntroState = true;
	ChangeAnimation("Intro");
	IntroSoundPlay();
}

void PirateBoss::IntroUpdate(float _Delta)
{
	if (IntroTimer < 0.0f)
	{
		IntroTimer = INTROTIMER;
		PirateRenderer->ChangeAnimation("Pirate_Intro_End");
	}

	IntroTimer -= _Delta;
}


void PirateBoss::IdleStart()
{
	ChangeAnimation("Idle");
}

void PirateBoss::IdleUpdate(float _Delta)
{
	if (IdleTimer < 0.0f && EBOSSPHASE::Phase1 == CurPhase)
	{
		IdleTimer = IDLETIMER;
		ChangeState(EPIRATEBOSSSTATE::Shoot);
		return;
	}

	if (IdleTimer < 0.0f && EBOSSPHASE::Phase2 == CurPhase)
	{
		IdleTimer = IDLETIMER;

		if (false == WhistleTime)
		{
			WhistleTime = true;
			ChangeState(EPIRATEBOSSSTATE::Shoot);
			return;
		}
		else
		{
			WhistleTime = false;
			ChangeState(EPIRATEBOSSSTATE::Whistle);
			return;
		}
	}

	IdleTimer -= _Delta;
}


void PirateBoss::ShootStart()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);
	ShootCount = Random.RandomInt(MINSHOOTCOUNT, MAXSHOOTCOUNT);

	ChangeAnimation("Shoot");
}

void PirateBoss::KnockoutStart()
{
	ChangeAnimation("Knockout");
}

void PirateBoss::WhistleStart()
{
	ChangeAnimation("Whistle");
}

void PirateBoss::WhistleUpdate(float _Delta)
{
	if (true == SummonDeathCheck() && 0 < SummonActors.size())
	{
		AllSummonDeath();
		ChangeState(EPIRATEBOSSSTATE::Idle);
		return;
	}
}

void PirateBoss::DeathStart()
{
	ChangeAnimation("Death");
	GameEngineSound::SoundPlay("sfx_pirate_fall_death.wav");
	PirateCollision->Off();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	Transform.SetLocalPosition({ WinScale.Half().X, 0.0f});
	PirateRenderer->SetAutoScaleRatio(0.8f);
	PirateRenderer->SetRenderOrder(ERENDERORDER::PrevMap2);
}

void PirateBoss::DeathUpdate(float _Delta)
{
	if (PirateDeathTimer < 0.0f)
	{
		float4 Pos = Transform.GetWorldPosition();
		float4 MovePos = float4::DOWN * _Delta * 700.0f;

		GameEngineColor CheckColor = Map::MainMap->GetColor(Pos, FLOORCOLOR);

		if (FLOORCOLOR != CheckColor)
		{
			Transform.AddLocalPosition(MovePos);
		}
		else
		{
			Death();
		}
	}

	PirateDeathTimer -= _Delta;
}