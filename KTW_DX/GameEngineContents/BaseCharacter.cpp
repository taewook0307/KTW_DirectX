#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Bullet.h"

BaseCharacter::BaseCharacter()
{
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Start()
{
	PlayerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Play);
	PlayerRenderer->CreateAnimation("CupHead_Intro", "Intro_Flex", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Idle", "Idle", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Run", "Run", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Jump", "Jump", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Parry", "Parry", 0.03f);
	PlayerRenderer->CreateAnimation("CupHead_Dash", "Dash_Ground", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Dash_Air", "Dash_Air", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Fall", "Jump", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Aim_Straight", "Aim_Straight", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Aim_StraightUp", "Aim_StraightUp", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Aim_StraightDown", "Aim_StraightDown", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Aim_Up", "Aim_Up", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Aim_Down", "Aim_Down", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Duck", "Duck", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Duck_Idle", "Duck_Idle", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Shoot_Straight", "Shoot_Straight", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_Shoot_Up", "Shoot_Up", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_Straight", "Shoot_Straight", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_StraightUp", "Shoot_StraightUp", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_StraightDown", "Shoot_StraightDown", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_Up", "Shoot_Up", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_AimShoot_Down", "Shoot_Down", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_RunShoot_Straight", "RunShoot_Straight", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_RunShoot_StraightUp", "RunShoot_StraightUp", 0.05f);
	PlayerRenderer->CreateAnimation("CupHead_DuckShoot", "Duck_Shoot", 0.05f);
	PlayerRenderer->AutoSpriteSizeOn();
	PlayerRenderer->SetAutoScaleRatio(0.8f);
	PlayerRenderer->SetPivotType(PivotType::Bottom);

	Dir = CharacterDir::Right;
	AimDir = CharacterAimDir::Straight;

	std::shared_ptr<GameEngineSprite> CharacterSprite = GameEngineSprite::Find("Idle");
	float4 SpriteScale = CharacterSprite->GetSpriteData(0).GetScale();

	PlayerCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Player);
	PlayerCollision->Transform.SetLocalScale(SpriteScale);

	ChangeState(CharacterState::Intro);
}

void BaseCharacter::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (CharacterDir::Left == Dir)
	{
		Transform.SetLocalScale({ -1.0f ,1.0f });
	}
	else
	{
		Transform.SetLocalScale({ 1.0f ,1.0f });
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
}

void BaseCharacter::DirChange()
{
	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsPress(VK_LEFT))
	{
		Dir = CharacterDir::Left;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT) || true == GameEngineInput::IsPress(VK_RIGHT))
	{
		Dir = CharacterDir::Right;
	}

	AimDirChange();
}

void BaseCharacter::AimDirChange()
{
	CharacterAimDir ChangeAimDir = CharacterAimDir::Straight;

	if (true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		ChangeAimDir = CharacterAimDir::StraightUp;
	}

	else if (true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		ChangeAimDir = CharacterAimDir::StraightDown;
	}

	else if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT) || true == GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeAimDir = CharacterAimDir::Straight;
	}

	else if (true == GameEngineInput::IsDown(VK_UP)
		|| true == GameEngineInput::IsPress(VK_UP))
	{
		ChangeAimDir = CharacterAimDir::Up;
	}

	else if (true == GameEngineInput::IsDown(VK_DOWN)
		|| true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeAimDir = CharacterAimDir::Down;
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
	case CharacterState::Intro:
		return IntroUpdate(_Delta);
	case CharacterState::Idle:
		return IdleUpdate(_Delta);
	case CharacterState::Run:
		return RunUpdate(_Delta);
	case CharacterState::Jump:
		return JumpUpdate(_Delta);
	case CharacterState::Parry:
		return ParryUpdate(_Delta);
	case CharacterState::Dash:
		return DashUpdate(_Delta);
	case CharacterState::Fall:
		return FallUpdate(_Delta);
	case CharacterState::Aim:
		return AimUpdate(_Delta);
	case CharacterState::Duck:
		return DuckUpdate(_Delta);
	case CharacterState::Shoot:
		return ShootUpdate(_Delta);
	case CharacterState::AimShoot:
		return AimShootUpdate(_Delta);
	case CharacterState::RunShoot:
		return RunShootUpdate(_Delta);
	case CharacterState::DuckShoot:
		return DuckShootUpdate(_Delta);
	default:
		break;
	}
}

void BaseCharacter::ChangeState(CharacterState _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case CharacterState::Intro:
			IntroStart();
			break;
		case CharacterState::Idle:
			IdleStart();
			break;
		case CharacterState::Run:
			RunStart();
			break;
		case CharacterState::Jump:
			JumpStart();
			break;
		case CharacterState::Parry:
			ParryStart();
			break;
		case CharacterState::Dash:
			DashStart();
			break;
		case CharacterState::Fall:
			FallStart();
			break;
		case CharacterState::Aim:
			AimStart();
			break;
		case CharacterState::Duck:
			DuckStart();
			break;
		case CharacterState::Shoot:
			ShootStart();
			break;
		case CharacterState::AimShoot:
			AimShootStart();
			break;
		case CharacterState::RunShoot:
			RunShootStart();
			break;
		case CharacterState::DuckShoot:
			DuckShootStart();
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
		if (CharacterAimDir::Straight == AimDir)
		{
			AnimationName += "_Straight";
		}
		else if (CharacterAimDir::Up == AimDir)
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
		if (CharacterAimDir::Straight == AimDir)
		{
			AnimationName += "_Straight";
		}
		else if (CharacterAimDir::StraightUp == AimDir)
		{
			AnimationName += "_StraightUp";
		}
		else
		{
			AnimationName += "_Straight";
		}
	}

	if ("Aim" == _State || "AimShoot" == _State)
	{
		if (CharacterAimDir::Straight == AimDir)
		{
			AnimationName += "_Straight";
		}
		else if (CharacterAimDir::StraightUp == AimDir)
		{
			AnimationName += "_StraightUp";
		}
		else if (CharacterAimDir::StraightDown == AimDir)
		{
			AnimationName += "_StraightDown";
		}
		else if (CharacterAimDir::Up == AimDir)
		{
			AnimationName += "_Up";
		}
		else if (CharacterAimDir::Down == AimDir)
		{
			AnimationName += "_Down";
		}
	}

	State = _State;

	PlayerRenderer->ChangeAnimation(AnimationName);
}