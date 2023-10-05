#include "PreCompile.h"
#include "ShipBoss.h"

ShipBoss::ShipBoss()
{
}

ShipBoss::~ShipBoss()
{
}

void ShipBoss::Start()
{
	ShipRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	ShipRenderer->CreateAnimation("Ship_Idle", "Ship_Idle");
	ShipRenderer->CreateAnimation("Ship_Attack", "Ship_Attack");
	ShipRenderer->SetEndEvent("Ship_Attack",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
	);

	ShipRenderer->AutoSpriteSizeOn();
	ShipRenderer->SetPivotType(PivotType::RightBottom);

	ChangeState(ESHIPBOSSSTATE::Idle);
}

void ShipBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('I'))
	{
		ChangeState(ESHIPBOSSSTATE::Attack);
		return;
	}
}

void ShipBoss::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case ESHIPBOSSSTATE::Idle:
		return IdleUpdate(_Delta);
	case ESHIPBOSSSTATE::Attack:
		return AttackUpdate(_Delta);
	default:
		break;
	}
}

void ShipBoss::ChangeState(ESHIPBOSSSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case ESHIPBOSSSTATE::Idle:
			IdleStart();
			break;
		case ESHIPBOSSSTATE::Attack:
			AttackStart();
			break;
		default:
			break;
		}
		CurState = _State;
	}
}

void ShipBoss::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Ship_";

	AnimationName += _State;

	State = _State;

	ShipRenderer->ChangeAnimation(AnimationName);
}