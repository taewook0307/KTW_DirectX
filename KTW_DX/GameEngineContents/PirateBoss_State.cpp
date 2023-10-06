#include "PreCompile.h"
#include "PirateBoss.h"

void PirateBoss::IntroStart()
{
	IsIntroState = true;
	ChangeAnimation("Intro");
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
	ChangeAnimation("Shoot");
}

void PirateBoss::ShootUpdate(float _Delta)
{

}


void PirateBoss::KnockoutStart()
{
	ChangeAnimation("Knockout");
}

void PirateBoss::KnockoutUpdate(float _Delta)
{

}


void PirateBoss::WhistleStart()
{
	ChangeAnimation("Whistle");
}

void PirateBoss::WhistleUpdate(float _Delta)
{

}