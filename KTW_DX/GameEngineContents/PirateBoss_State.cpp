#include "PreCompile.h"
#include "PirateBoss.h"

void PirateBoss::IdleStart()
{
	ChangeAnimation("Idle");
}

void PirateBoss::IdleUpdate(float _Delta)
{
	if (IdleTimer < 0.0f)
	{
		IdleTimer = IDLETIMER;
		ChangeState(EPIRATEBOSSSTATE::Shoot);
		return;
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


void PirateBoss::LaughStart()
{
	ChangeAnimation("Laugh");
}

void PirateBoss::LaughUpdate(float _Delta)
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