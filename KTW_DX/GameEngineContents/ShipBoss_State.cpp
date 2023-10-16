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

	if (0.0f > IdleTimer /*&& EBOSSPHASE::Phase3 != CurPhase*/)
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

void ShipBoss::BeamStart()
{
	ChangeAnimation("Beam");
}

void ShipBoss::DeathStart()
{
	BodyCollision->Off();
	StageLevel::StageClear();
	ChangeAnimation("Death");
}