#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Bullet.h"
#include "JumpDust.h"

BaseCharacter* BaseCharacter::MainCharacter = nullptr;

BaseCharacter::BaseCharacter()
{
	MainCharacter = this;
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Start()
{
	PlayerRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Play);
	PlayerRenderer->CreateAnimation("CupHead_Intro", "Intro_Flex", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Idle", "Idle", IDLEINTER);
	PlayerRenderer->CreateAnimation("CupHead_Run", "Run", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_Run", 1,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateRunDust();
		}
	);
	PlayerRenderer->SetFrameEvent("CupHead_Run", 9,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateRunDust();
		}
	);
	PlayerRenderer->CreateAnimation("CupHead_Jump", "Jump", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Parry", "Parry", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetEndEvent("CupHead_Parry",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ECHARACTERSTATE::Fall);
			return;
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_Dash", "Dash_Ground", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_Dash", 0,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateDashDust(Dir);
		}
	);
	PlayerRenderer->CreateAnimation("CupHead_Dash_Air", "Dash_Air", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_Dash_Air", 0,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateDashDust(Dir);
		}
	);
	PlayerRenderer->CreateAnimation("CupHead_Fall", "Jump", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Aim_Straight", "Aim_Straight", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Aim_StraightUp", "Aim_StraightUp", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Aim_StraightDown", "Aim_StraightDown", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Aim_Up", "Aim_Up", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Aim_Down", "Aim_Down", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Duck", "Duck", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetEndEvent("CupHead_Duck",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			if (true == GameEngineInput::IsPress(VK_DOWN))
			{
				ChangeAnimation("Duck_Idle");
			}
		}
	);
	PlayerRenderer->CreateAnimation("CupHead_Duck_Idle", "Duck_Idle", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Shoot_Straight", "Shoot_Straight", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_Shoot_Up", "Shoot_Up", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_Straight", "Shoot_Straight", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_StraightUp", "Shoot_StraightUp", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_StraightDown", "Shoot_StraightDown", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_Up", "Shoot_Up", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_Down", "Shoot_Down", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_RunShoot_Straight", "RunShoot_Straight", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_RunShoot_StraightUp", "RunShoot_StraightUp", CHARACTERANIMATIONINTER);
	PlayerRenderer->CreateAnimation("CupHead_DuckShoot", "Duck_Shoot", CHARACTERANIMATIONINTER);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Up", "Special_Up", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Up", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Down", "Special_Down", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Down", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Straight", "Special_Straight", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Straight", 6, 
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);
	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_StraightUp", "Special_StraightUp", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_StraightUp", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_StraightDown", "Special_StraightDown", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_StraightDown", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Air_Up", "SpecialAir_Up", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Air_Up", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Air_Down", "SpecialAir_Down", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Air_Down", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Air_Straight", "SpecialAir_Straight", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Air_Straight", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Air_StraightUp", "SpecialAir_StraightUp", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Air_StraightUp", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_SpecialAttack_Air_StraightDown", "SpecialAir_StraightDown", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetFrameEvent("CupHead_SpecialAttack_Air_StraightDown", 6,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SpecialShootState();
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_Hit", "Hit_Ground", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetEndEvent("CupHead_Hit",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ECHARACTERSTATE::Idle);
			return;
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_Hit_Air", "Hit_Air", CHARACTERANIMATIONINTER);
	PlayerRenderer->SetEndEvent("CupHead_Hit_Air",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(ECHARACTERSTATE::Fall);
			return;
		}
	);

	PlayerRenderer->CreateAnimation("CupHead_Death", "Death", 0.1f);

	PlayerRenderer->AutoSpriteSizeOn();
	PlayerRenderer->SetAutoScaleRatio(0.8f);
	PlayerRenderer->SetPivotType(PivotType::Bottom);

	Dir = EACTORDIR::Right;
	AimDir = ECHARACTERAIMDIR::Straight;

	std::shared_ptr<GameEngineSprite> CharacterSprite = GameEngineSprite::Find("Idle");
	float4 CollisionScale = CharacterSprite->GetSpriteData(0).GetScale().Half();
	float4 CollisionPosition = { 0.0f, CollisionScale.Half().Y};

	PlayerCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::Player);
	PlayerCollision->Transform.SetLocalScale(CollisionScale);
	PlayerCollision->Transform.SetLocalPosition(CollisionPosition);

	ChangeState(ECHARACTERSTATE::Intro);
}

void BaseCharacter::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (EACTORDIR::Left == Dir)
	{
		PlayerRenderer->LeftFlip();
	}
	else
	{
		PlayerRenderer->RightFlip();
	}

	if (true == GameEngineInput::IsDown('V'))
	{
		ChangeState(ECHARACTERSTATE::SpecialAttack);
	}

	if (true == Cheat && true == GameEngineInput::IsPress('V'))
	{
		ChangeState(ECHARACTERSTATE::SpecialAttack);
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		Cheat = !Cheat;
	}

	if (true == Shoot)
	{
		ShootTimer -= _Delta;

		if (ShootTimer < 0.0f)
		{
			Shoot = false;
			ShootTimer = SHOOTTIMER;
		}
	}

	if (true == NoDamage)
	{
		NoDamageTimer -= _Delta;

		if (NoDamageTimer < 0.0f)
		{
			NoDamage = false;
			NoDamageTimer = NODAMAGETIMER;
		}
	}

	if (true == ParrySuccess)
	{
		float4 ParryPos = float4::UP * JUMPPOWER * 0.7f;
		SetGravityForce(ParryPos);
		ParrySuccess = false;
	}

	PlayerCollision->Collision(ECOLLISIONORDER::MonsterBody,
		[=](std::vector<std::shared_ptr<GameEngineCollision>>& _ColVector)
		{
			if (ECHARACTERSTATE::Hit != CurState && false == NoDamage)
			{
				ChangeState(ECHARACTERSTATE::Hit);
				return;
			}
			
		}
	);

	PlayerCollision->Collision(ECOLLISIONORDER::MonsterAttack,
		[=](std::vector<std::shared_ptr<GameEngineCollision>>& _ColVector)
		{
			if (ECHARACTERSTATE::Hit != CurState && false == NoDamage)
			{
				ChangeState(ECHARACTERSTATE::Hit);
				return;
			}

		}
	);
}

void BaseCharacter::DirChange()
{
	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsPress(VK_LEFT))
	{
		Dir = EACTORDIR::Left;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT) || true == GameEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EACTORDIR::Right;
	}

	AimDirChange();
}

void BaseCharacter::AimDirChange()
{
	ECHARACTERAIMDIR ChangeAimDir = ECHARACTERAIMDIR::Straight;

	if (true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		ChangeAimDir = ECHARACTERAIMDIR::StraightUp;
	}

	else if (true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		ChangeAimDir = ECHARACTERAIMDIR::StraightDown;
	}

	else if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT) || true == GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeAimDir = ECHARACTERAIMDIR::Straight;
	}

	else if (true == GameEngineInput::IsDown(VK_UP)
		|| true == GameEngineInput::IsPress(VK_UP))
	{
		ChangeAimDir = ECHARACTERAIMDIR::Up;
	}

	else if (true == GameEngineInput::IsDown(VK_DOWN)
		|| true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeAimDir = ECHARACTERAIMDIR::Down;
	}

	if (ChangeAimDir != AimDir)
	{
		AimDir = ChangeAimDir;
		ChangeAnimation(State);
	}
}

void BaseCharacter::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case ECHARACTERSTATE::Intro:
		return IntroUpdate(_Delta);
	case ECHARACTERSTATE::Idle:
		return IdleUpdate(_Delta);
	case ECHARACTERSTATE::Run:
		return RunUpdate(_Delta);
	case ECHARACTERSTATE::Jump:
		return JumpUpdate(_Delta);
	case ECHARACTERSTATE::Parry:
		return ParryUpdate(_Delta);
	case ECHARACTERSTATE::Dash:
		return DashUpdate(_Delta);
	case ECHARACTERSTATE::Fall:
		return FallUpdate(_Delta);
	case ECHARACTERSTATE::Aim:
		return AimUpdate(_Delta);
	case ECHARACTERSTATE::Duck:
		return DuckUpdate(_Delta);
	case ECHARACTERSTATE::Shoot:
		return ShootUpdate(_Delta);
	case ECHARACTERSTATE::AimShoot:
		return AimShootUpdate(_Delta);
	case ECHARACTERSTATE::RunShoot:
		return RunShootUpdate(_Delta);
	case ECHARACTERSTATE::DuckShoot:
		return DuckShootUpdate(_Delta);
	case ECHARACTERSTATE::SpecialAttack:
		return SpecialAttackUpdate(_Delta);
	case ECHARACTERSTATE::Hit:
		return HitUpdate(_Delta);
	case ECHARACTERSTATE::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void BaseCharacter::ChangeState(ECHARACTERSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case ECHARACTERSTATE::Intro:
			IntroStart();
			break;
		case ECHARACTERSTATE::Idle:
			IdleStart();
			break;
		case ECHARACTERSTATE::Run:
			RunStart();
			break;
		case ECHARACTERSTATE::Jump:
			JumpStart();
			break;
		case ECHARACTERSTATE::Parry:
			ParryStart();
			break;
		case ECHARACTERSTATE::Dash:
			DashStart();
			break;
		case ECHARACTERSTATE::Fall:
			FallStart();
			break;
		case ECHARACTERSTATE::Aim:
			AimStart();
			break;
		case ECHARACTERSTATE::Duck:
			DuckStart();
			break;
		case ECHARACTERSTATE::Shoot:
			ShootStart();
			break;
		case ECHARACTERSTATE::AimShoot:
			AimShootStart();
			break;
		case ECHARACTERSTATE::RunShoot:
			RunShootStart();
			break;
		case ECHARACTERSTATE::DuckShoot:
			DuckShootStart();
			break;
		case ECHARACTERSTATE::SpecialAttack:
			SpecialAttackStart();
			break;
		case ECHARACTERSTATE::Hit:
			HitStart();
			break;
		case ECHARACTERSTATE::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void BaseCharacter::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "CupHead_";

	AnimationName += _State;

	if ("Shoot" == _State)
	{
		if (ECHARACTERAIMDIR::Straight == AimDir)
		{
			AnimationName += "_Straight";
		}
		else if (ECHARACTERAIMDIR::Up == AimDir)
		{
			AnimationName += "_Up";
		}
		else
		{
			AnimationName += "_Straight";
		}
	}

	if ("RunShoot" == _State)
	{
		if (ECHARACTERAIMDIR::Straight == AimDir)
		{
			AnimationName += "_Straight";
		}
		else if (ECHARACTERAIMDIR::StraightUp == AimDir)
		{
			AnimationName += "_StraightUp";
		}
		else
		{
			AnimationName += "_Straight";
		}
	}

	if ("Aim" == _State
		|| "AimShoot" == _State
		|| "SpecialAttack" == _State
		|| "SpecialAttack_Air" == _State)
	{
		if (ECHARACTERAIMDIR::Straight == AimDir)
		{
			AnimationName += "_Straight";
		}
		else if (ECHARACTERAIMDIR::StraightUp == AimDir)
		{
			AnimationName += "_StraightUp";
		}
		else if (ECHARACTERAIMDIR::StraightDown == AimDir)
		{
			AnimationName += "_StraightDown";
		}
		else if (ECHARACTERAIMDIR::Up == AimDir)
		{
			AnimationName += "_Up";
		}
		else if (ECHARACTERAIMDIR::Down == AimDir)
		{
			AnimationName += "_Down";
		}
	}

	State = _State;

	PlayerRenderer->ChangeAnimation(AnimationName);
}