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
		IdleTimer = SHIPIDLETIMER;
		ChangeState(ESHIPBOSSSTATE::Wince);
		return;
	}

	if (0.0f > IdleTimer && EBOSSPHASE::Phase3 != CurPhase)
	{
		IdleTimer = SHIPIDLETIMER;
		ChangeState(ESHIPBOSSSTATE::Attack);
		return;
	}

	if (0.0f > IdleTimer && EBOSSPHASE::Phase3 == CurPhase && true == ChangeShip)
	{
		IdleTimer = SHIPIDLETIMER;
		ChangeState(ESHIPBOSSSTATE::Charge);
		return;
	}

	IdleTimer -= _Delta;
}

void ShipBoss::AttackStart()
{
	ChangeAnimation("Attack");
}

void ShipBoss::AttackUpdate(float _Delta)
{
	if (EBOSSPHASE::Phase3 != CurPhase)
	{
		if (true == ShipRenderer->IsCurAnimationEnd())
		{
			--CannonAttackCount;
		}

		if (0 >= CannonAttackCount)
		{
			CannonAttackCount = CANNONATTACKCOUNT;
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
		else
		{
			ChangeState(ESHIPBOSSSTATE::Attack);
			return;
		}
	}
	else
	{
		
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
	ChangeAnimation("Charge");
}

void ShipBoss::DeathStart()
{
	StageLevel::StageClear();
	ChangeAnimation("Death");
}