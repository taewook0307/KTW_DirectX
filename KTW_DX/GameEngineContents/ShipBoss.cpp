#include "PreCompile.h"
#include "ShipBoss.h"

#include "PirateBoss.h"
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

	ShipRenderer->CreateAnimation("Ship_Wince", "Ship_Wince", 0.1f, -1, -1, false);
	ShipRenderer->SetEndEvent("Ship_Wince",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Transform);
			return;
		}
	);

	ShipRenderer->CreateAnimation("Ship_Transform", "Ship_Transform", 0.1f, -1, -1, false);
	ShipRenderer->SetFrameEvent("Ship_Transform", 3,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateBoss::MainPirateBoss->ChangePhase3();
		}
	);
	
	ShipRenderer->SetEndEvent("Ship_Transform",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeShip = true;
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Idle", "Ship_Phase3_Idle", SHIPANIMATIONINTER);

	ShipRenderer->CreateAnimation("Ship_Phase3_Charge", "Ship_Phase3_Charge", 0.1f, -1, -1, false);
	ShipRenderer->SetEndEvent("Ship_Phase3_Charge",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Attack);
			return;
		}
	);
	ShipRenderer->CreateAnimation("Ship_Phase3_Attack", "Ship_Phase3_Attack", 0.1f);
	ShipRenderer->SetEndEvent("Ship_Phase3_Attack",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
	);
	ShipRenderer->CreateAnimation("Ship_Phase3_Death", "Ship_Phase3_Death", 0.1f);

	ShipRenderer->AutoSpriteSizeOn();
	ShipRenderer->SetPivotType(PivotType::RightBottom);


	ShipPrevRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PrevBoss1);
	ShipPrevRenderer->CreateAnimation("Ship_Phase3_Idle_Prev", "Ship_Phase3_Idle_Prev", SHIPANIMATIONINTER);
	ShipPrevRenderer->AutoSpriteSizeOn();
	ShipPrevRenderer->SetPivotType(PivotType::RightBottom);
	ShipPrevRenderer->Off();

	ChangeState(ESHIPBOSSSTATE::Idle);
}

void ShipBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('O'))
	{
		ChangeState(ESHIPBOSSSTATE::Death);
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

void ShipBoss::ChangeState(ESHIPBOSSSTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
		{
		case ESHIPBOSSSTATE::Idle:
			IdleStart();
			break;
		case ESHIPBOSSSTATE::Attack:
			AttackStart();
			break;
		case ESHIPBOSSSTATE::Wince:
			WinceStart();
			break;
		case ESHIPBOSSSTATE::Transform:
			TransformStart();
			break;
		case ESHIPBOSSSTATE::Charge:
			ChargeStart();
			break;
		case ESHIPBOSSSTATE::Death:
			DeathStart();
			break;
		default:
			break;
		}
		CurState = _CurState;
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