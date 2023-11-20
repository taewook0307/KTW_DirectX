#include "PreCompile.h"
#include "ShipBoss.h"

#include "PirateBoss.h"
#include "CannonBall.h"
#include "CannonBallDust.h"
#include "ShipBubble.h"
#include "ShipBeam.h"

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
	ShipRenderer->SetFrameEvent("Ship_Attack", 5,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_pirate_boat_cannon_chew.wav");
		}
	);

	ShipRenderer->SetFrameEvent("Ship_Attack", 19,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_pirate_boat_cannon_fire.wav");
			CreateCannonBall();
		}
	);

	ShipRenderer->CreateAnimation("Ship_Wince", "Ship_Wince", SHIPANIMATIONINTER, -1, -1, false);
	ShipRenderer->CreateAnimation("Ship_Wince_Loop", "Ship_Wince", SHIPANIMATIONINTER, 1, 8, true);
	ShipRenderer->SetEndEvent("Ship_Wince",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ShipRenderer->ChangeAnimation("Ship_Wince_Loop");
		}
	);

	ShipRenderer->CreateAnimation("Ship_Transform", "Ship_Transform", SHIPANIMATIONINTER, 0, 10, false);
	ShipRenderer->SetFrameEvent("Ship_Transform", 3,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PirateBoss::MainPirateBoss->ChangePhase3();
			ShipRailRenderer->Death();
			ShipSailRenderer->Death();
			ShipMastRenderer->Death();
		}
	);
	ShipRenderer->SetEndEvent("Ship_Transform",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ShipRenderer->ChangeAnimation("Ship_Transform_Loop");
		}
	);

	ShipRenderer->CreateAnimation("Ship_Transform_Loop", "Ship_Transform", SHIPANIMATIONINTER, 9, 10, true);
	ShipRenderer->CreateAnimation("Ship_Transform_End", "Ship_Transform", SHIPANIMATIONINTER, 10, -1, false);
	ShipRenderer->SetEndEvent("Ship_Transform_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeShip = true;
			BodyCollision->On();
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Idle", "Ship_Phase3_Idle", SHIPANIMATIONINTER);

	ShipRenderer->CreateAnimation("Ship_Phase3_Attack", "Ship_Phase3_Attack", SHIPANIMATIONINTER);
	ShipRenderer->SetFrameEvent("Ship_Phase3_Attack", 8,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BubbleShootSoundPlay();
			CreateBubble();
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Charge_Start", "Ship_Phase3_Charge", SHIPANIMATIONINTER, 0, 5, false);
	ShipRenderer->SetEndEvent("Ship_Phase3_Charge_Start",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ShipRenderer->ChangeAnimation("Ship_Phase3_Charge");
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Charge", "Ship_Phase3_Charge", SHIPANIMATIONINTER, 6, 8, true);
	ShipRenderer->CreateAnimation("Ship_Phase3_Charge_End", "Ship_Phase3_Charge", SHIPANIMATIONINTER, 9, -1, false);
	ShipRenderer->SetEndEvent("Ship_Phase3_Charge_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BodyCollision->On();
			ChangeState(ESHIPBOSSSTATE::Beam);
			return;
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Beam_Start", "Ship_Phase3_Beam", SHIPANIMATIONINTER, 0, 2, false);
	ShipRenderer->SetStartEvent("Ship_Phase3_Beam_Start",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateBeam();
			GameEngineSound::SoundPlay("sfx_pirate_boat_beam_fire.wav");
		}
	);
	ShipRenderer->SetEndEvent("Ship_Phase3_Beam_Start",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ShipRenderer->ChangeAnimation("Ship_Phase3_Beam");
			return;
		}
	);

	ShipRenderer->CreateAnimation("Ship_Phase3_Beam", "Ship_Phase3_Beam", SHIPANIMATIONINTER, 3, 4);

	ShipRenderer->CreateAnimation("Ship_Phase3_Beam_End", "Ship_Phase3_Beam", SHIPANIMATIONINTER, 5, -1, false);
	ShipRenderer->SetEndEvent("Ship_Phase3_Beam_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ESHIPBOSSSTATE::Idle);
			return;
		}
	);
	
	ShipRenderer->CreateAnimation("Ship_Phase3_Death", "Ship_Phase3_Death", 0.1f, 0, 8, false);
	ShipRenderer->SetEndEvent("Ship_Phase3_Death",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ShipRenderer->ChangeAnimation("Ship_Phase3_Death_Reverse");
		}
	);
	ShipRenderer->CreateAnimation("Ship_Phase3_Death_Reverse", "Ship_Phase3_Death", 0.1f, 8, 0, false);
	ShipRenderer->SetEndEvent("Ship_Phase3_Death_Reverse",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ShipRenderer->ChangeAnimation("Ship_Phase3_Death");
		}
	);

	ShipRenderer->AutoSpriteSizeOn();
	ShipRenderer->SetPivotType(PivotType::RightBottom);

	BodyCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossBody);
	BodyCollision->Transform.SetLocalScale({ 70.0f, 90.0f });
	BodyCollision->Transform.SetLocalPosition({ -155.0f, 380.0f });
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Off();

	ChangeState(ESHIPBOSSSTATE::Idle);
}

void ShipBoss::Update(float _Delta)
{
	OutputDebugStringA(std::to_string(AttackCount).c_str());
	OutputDebugStringA("\n");

	StateUpdate(_Delta);

	if (PHASE3HP < HitCount && ESHIPBOSSSTATE::Death != CurState)
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
	case ESHIPBOSSSTATE::Charge:
		return ChargeUpdate(_Delta);
	case ESHIPBOSSSTATE::Beam:
		return BeamUpdate(_Delta);
	case ESHIPBOSSSTATE::Wince:
		return WinceUpdate(_Delta);
	case ESHIPBOSSSTATE::Transform:
		return TransformUpdate(_Delta);
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

void ShipBoss::CreateBeam()
{
	float4 ShipPos = Transform.GetWorldPosition();
	float4 CreatePos = { ShipPos.X - 150.0f, ShipPos.Half().Y - 30.0f };

	std::shared_ptr<ShipBeam> CurBeam = GetLevel()->CreateActor<ShipBeam>(EUPDATEORDER::Bullet);
	CurBeam->Transform.SetLocalPosition(CreatePos);
}

void ShipBoss::BubbleShootSoundPlay()
{
	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_pirate_boat_uvula_shoot_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_pirate_boat_uvula_shoot_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_pirate_boat_uvula_shoot_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_pirate_boat_uvula_shoot_04.wav");
		break;
	}
}