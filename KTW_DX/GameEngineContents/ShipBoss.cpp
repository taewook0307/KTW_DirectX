#include "PreCompile.h"
#include "ShipBoss.h"

#include "PirateBoss.h"
#include "CannonBall.h"
#include "CannonBallDust.h"
#include "ShipBubble.h"

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
	GameEngineInput::AddInputObject(this);

	ShipRailRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	ShipRailRenderer->CreateAnimation("Ship_Rail", "Ship_Rail", SHIPANIMATIONINTER);
	ShipRailRenderer->AutoSpriteSizeOn();
	ShipRailRenderer->SetPivotType(PivotType::Bottom);
	ShipRailRenderer->Transform.SetLocalPosition(SHIPRAILPOS);
	ShipRailRenderer->ChangeAnimation("Ship_Rail");

	ShipSailRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PrevBoss1);
	ShipSailRenderer->CreateAnimation("Ship_Sail", "Ship_Sail");
	ShipSailRenderer->AutoSpriteSizeOn();
	ShipSailRenderer->SetPivotType(PivotType::Bottom);
	ShipSailRenderer->Transform.SetLocalPosition(SHIPSAILPOS);
	ShipSailRenderer->ChangeAnimation("Ship_Sail");

	ShipMastRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PrevBoss);
	ShipMastRenderer->SetSprite("pirate_boatMast.Png");
	ShipMastRenderer->SetPivotType(PivotType::Bottom);
	ShipMastRenderer->Transform.SetLocalPosition(SHIPMASTPOS);

	ShipRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	ShipRenderer->CreateAnimation("Ship_Idle", "Ship_Idle", SHIPANIMATIONINTER);
	ShipRenderer->CreateAnimation("Ship_Attack", "Ship_Attack", SHIPANIMATIONINTER);

	ShipRenderer->SetFrameEvent("Ship_Attack", 19,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateCannonBall();
		}
	);

	ShipRenderer->CreateAnimation("Ship_Wince", "Ship_Wince", SHIPANIMATIONINTER, -1, -1, false);
	ShipRenderer->SetEndEvent("Ship_Wince",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Transform);
			return;
		}
	);

	ShipRenderer->CreateAnimation("Ship_Transform", "Ship_Transform", SHIPANIMATIONINTER, -1, -1, false);
	/*ShipRenderer->SetFrameEvent("Ship_Transform", 3,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateBoss::MainPirateBoss->ChangePhase3();
		}
	);*/
	
	ShipRenderer->SetEndEvent("Ship_Transform",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeShip = true;
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Idle", "Ship_Phase3_Idle", SHIPANIMATIONINTER);

	ShipRenderer->CreateAnimation("Ship_Phase3_Attack", "Ship_Phase3_Attack", SHIPANIMATIONINTER);
	ShipRenderer->SetFrameEvent("Ship_Phase3_Attack", 8,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateBubble();
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Charge", "Ship_Phase3_Charge", SHIPANIMATIONINTER, -1, -1, false);
	ShipRenderer->SetEndEvent("Ship_Phase3_Charge",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Beam);
			return;
		}
	);
	ShipRenderer->CreateAnimation("Ship_Phase3_Beam", "Ship_Phase3_Beam", SHIPANIMATIONINTER);
	ShipRenderer->SetEndEvent("Ship_Phase3_Beam",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
	);
	ShipRenderer->CreateAnimation("Ship_Phase3_Death", "Ship_Phase3_Death", SHIPANIMATIONINTER);

	ShipRenderer->AutoSpriteSizeOn();
	ShipRenderer->SetPivotType(PivotType::RightBottom);

	ChangeState(ESHIPBOSSSTATE::Idle);
}

void ShipBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('O', this))
	{
		ChangeState(ESHIPBOSSSTATE::Wince);
		CurPhase = EBOSSPHASE::Phase3;
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
		case ESHIPBOSSSTATE::Beam:
			BeamStart();
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
	float4 ShipPos = Transform.GetWorldPosition();
	float4 CreatePos = { ShipPos.X - 480.0f, ShipPos.Y + 90.0f };

	std::shared_ptr NewCannonBall = GetLevel()->CreateActor<CannonBall>(EUPDATEORDER::Bullet);
	NewCannonBall->Transform.SetLocalPosition(CreatePos);

	std::shared_ptr Effect = GetLevel()->CreateActor<CannonBallDust>(EUPDATEORDER::Effect);
	Effect->Transform.SetLocalPosition(CreatePos);
}

void ShipBoss::CreateBubble()
{
	float4 ShipPos = Transform.GetWorldPosition();
	float4 CreatePos = { ShipPos.X - 480.0f, ShipPos.Half().Y };

	std::shared_ptr<ShipBubble> CurBubble = GetLevel()->CreateActor<ShipBubble>(EUPDATEORDER::Bullet);
	CurBubble->Transform.SetLocalPosition(CreatePos);
}