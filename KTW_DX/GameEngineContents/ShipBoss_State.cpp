#include "PreCompile.h"
#include "ShipBoss.h"

#include "StageLevel.h"

void ShipBoss::IdleStart()
{
	ChangeAnimation("Idle");
}

void ShipBoss::IdleUpdate(float _Delta)
{
	if (EBOSSPHASE::Phase3 == CurPhase && false == ChangeShip)
	{
		IdleTimer = PHASE3SHIPIDLETIMER;
		ChangeState(ESHIPBOSSSTATE::Wince);
		return;
	}

	if (0.0f > IdleTimer)
	{
		if (EBOSSPHASE::Phase1 == CurPhase)
		{
			IdleTimer = PHASE1SHIPIDLETIMER;
		}
		else if (EBOSSPHASE::Phase2 == CurPhase)
		{
			IdleTimer = PHASE2SHIPIDLETIMER;
		}
		else
		{
			IdleTimer = PHASE3SHIPIDLETIMER;
		}
		

		if (EBOSSPHASE::Phase3 != CurPhase)
		{
			ChangeState(ESHIPBOSSSTATE::Attack);
			return;
		}
		else
		{
			if (0 < AttackCount)
			{
				ChangeState(ESHIPBOSSSTATE::Attack);
				return;
			}
			else
			{
				AttackCount = ATTACKCOUNT;
				ChangeState(ESHIPBOSSSTATE::Charge);
				return;
			}
		}
	}

	IdleTimer -= _Delta;
}

void ShipBoss::AttackStart()
{
	ChangeAnimation("Attack");
}

void ShipBoss::AttackUpdate(float _Delta)
{
	if (true == ShipRenderer->IsCurAnimationEnd())
	{
		if (EBOSSPHASE::Phase3 == CurPhase && true == ShipRenderer->IsCurAnimation("Ship_Phase3_Attack"))
		{
			--AttackCount;
		}

		ChangeState(ESHIPBOSSSTATE::Idle);
		return;
	}	
}

void ShipBoss::WinceStart()
{
	ChangeAnimation("Wince");
}

void ShipBoss::TransformStart()
{
	ChangeAnimation("Transform");
}

void ShipBoss::ChargeStart()
{
	BodyCollision->Off();
	ChangeAnimation("Charge_Start");
}

void ShipBoss::ChargeUpdate(float _Delta)
{
	if (0.0f > ChargeTimer)
	{
		ChargeTimer = SHIPCHARGETIMER;
		ShipRenderer->ChangeAnimation("Ship_Phase3_Charge_End");
		return;
	}

	ChargeTimer -= _Delta;
}

void ShipBoss::BeamStart()
{
	ChangeAnimation("Beam_Start");
}

void ShipBoss::BeamUpdate(float _Delta)
{
	if (0.0f > BeamTimer)
	{
		BeamTimer = SHIPBEAMTIMER;
		ShipRenderer->ChangeAnimation("Ship_Phase3_Beam_End");
		return;
	}

	BeamTimer -= _Delta;
}

void ShipBoss::DeathStart()
{
	BodyCollision->Off();
	StageLevel::StageClear();
	ChangeAnimation("Death");
}