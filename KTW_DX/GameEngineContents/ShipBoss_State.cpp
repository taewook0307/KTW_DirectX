#include "PreCompile.h"
#include "ShipBoss.h"

void ShipBoss::IdleStart()
{
	ChangeAnimation("Idle");
}

void ShipBoss::IdleUpdate(float _Delta)
{
	if (0.0f > IdleTimer)
	{
		IdleTimer = SHIPIDLETIMER;
		ChangeState(ESHIPBOSSSTATE::Attack);
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