#include "PreCompile.h"
#include "ShipBoss.h"

#include "StageLevel.h"

void ShipBoss::IdleStart()
{
	ChangeAnimation("Idle");
	if (EBOSSPHASE::Phase3 == CurPhase)
	{
		ShipPrevRenderer->On();
		ShipPrevRenderer->ChangeAnimation("Ship_Phase3_Idle_Prev");
	}
}

void ShipBoss::IdleUpdate(float _Delta)
{
	if (EBOSSPHASE::Phase3 == CurPhase && false == ChangeShip)
	{
		IdleTimer = SHIPIDLETIMER;
		ShipPrevRenderer->Off();
		ChangeState(ESHIPBOSSSTATE::Wince);
		return;
	}

	if (0.0f > IdleTimer /*&& EBOSSPHASE::Phase3 != CurPhase*/)
	{
		IdleTimer = SHIPIDLETIMER;
		ShipPrevRenderer->Off();
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
	StageLevel::StageClear();
	ChangeAnimation("Death");
}