#include "PreCompile.h"
#include "ShipBoss.h"

#include "CannonBall.h"
#include "CannonBallDust.h"

ShipBoss* ShipBoss::MainShip = nullptr;

ShipBoss::ShipBoss()
{
	MainShip = this;
}

ShipBoss::~ShipBoss()
{
}

void ShipBoss::Start()
{
	ShipRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	ShipRenderer->CreateAnimation("Ship_Idle", "Ship_Idle", SHIPANIMATIONINTER);
	ShipRenderer->CreateAnimation("Ship_Attack", "Ship_Attack", SHIPANIMATIONINTER);

	ShipRenderer->SetFrameEvent("Ship_Attack", 19,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateCannonBall();
		}
	);

	ShipRenderer->CreateAnimation("Ship_Transform", "Ship_Transform", 0.1f, -1, -1, false);
	ShipRenderer->SetEndEvent("Ship_Transform",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeShip = true;
		}
	);

	ShipRenderer->AutoSpriteSizeOn();
	ShipRenderer->SetPivotType(PivotType::RightBottom);

	ChangeState(ESHIPBOSSSTATE::Idle);
}

void ShipBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (EBOSSPHASE::Phase3 == CurPhase)
	{
		ChangeState(ESHIPBOSSSTATE::Transform);
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
	case ESHIPBOSSSTATE::Transform:
		return TransformUpdate(_Delta);
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
		case ESHIPBOSSSTATE::Transform:
			TransformStart();
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

	if (EBOSSPHASE::Phase3 == CurPhase && true == ChangeShip)
	{
		AnimationName += "Phase3_";
	}

	AnimationName += _State;

	State = _State;

	ShipRenderer->ChangeAnimation(AnimationName);
}

void ShipBoss::CreateCannonBall()
{
	std::shared_ptr NewCannonBall = GetLevel()->CreateActor<CannonBall>(EUPDATEORDER::Bullet);
	float4 ShipPos = Transform.GetWorldPosition();
	float4 CreatePos = { ShipPos.X - 480.0f, ShipPos.Y + 90.0f };

	NewCannonBall->Transform.SetLocalPosition(CreatePos);

	std::shared_ptr Effect = GetLevel()->CreateActor<CannonBallDust>(EUPDATEORDER::Effect);
	Effect->Transform.SetLocalPosition(CreatePos);
}