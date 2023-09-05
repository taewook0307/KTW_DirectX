#include "PreCompile.h"
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Play);
	MainSpriteRenderer->CreateAnimation("CupHead_Idle", "Idle");
	MainSpriteRenderer->CreateAnimation("CupHead_Run", "Run", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Jump", "Jump", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Dash", "Dash_Air", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Fall", "Jump", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Aim_Straight", "Aim_Straight", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Aim_StraightUp", "Aim_StraightUp", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Aim_StraightDown", "Aim_StraightDown", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Aim_Up", "Aim_Up", 0.05f);
	MainSpriteRenderer->CreateAnimation("CupHead_Aim_Down", "Aim_Down", 0.05f);
	MainSpriteRenderer->ChangeAnimation("CupHead_Idle");
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetAutoScaleRatio(0.8f);

	Dir = CharacterDir::Right;
	AimDir = CharacterAimDir::Right;
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
}

void BaseCharacter::AimDirChange()
{
	if (true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_LEFT))
	{
		AimDir = CharacterAimDir::Left;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{
		AimDir = CharacterAimDir::Right;
	}

	if (true == GameEngineInput::IsDown(VK_UP)
		|| true == GameEngineInput::IsPress(VK_UP))
	{
		AimDir = CharacterAimDir::Up;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN)
		|| true == GameEngineInput::IsPress(VK_DOWN))
	{
		AimDir = CharacterAimDir::Down;
	}

	if (true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_RIGHT))
	{
		AimDir = CharacterAimDir::RightUp;
	}

	if (true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		AimDir = CharacterAimDir::LeftUp;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_RIGHT))
	{
		AimDir = CharacterAimDir::RightDown;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		AimDir = CharacterAimDir::LeftDown;
	}

	ChangeState(CurState);
}

void BaseCharacter::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case CharacterState::Idle:
		return IdleUpdate(_Delta);
	case CharacterState::Run:
		return RunUpdate(_Delta);
	case CharacterState::Jump:
		return JumpUpdate(_Delta);
	case CharacterState::Dash:
		return DashUpdate(_Delta);
	case CharacterState::Fall:
		return FallUpdate(_Delta);
	case CharacterState::Aim:
		return AimUpdate(_Delta);
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
		case CharacterState::Idle:
			IdleStart();
			break;
		case CharacterState::Run:
			RunStart();
			break;
		case CharacterState::Jump:
			JumpStart();
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

	if (_State == "Aim")
	{
		if (CharacterAimDir::Left == AimDir || CharacterAimDir::Right == AimDir)
		{
			AnimationName += "_Straight";
		}
		else if (CharacterAimDir::LeftUp == AimDir || CharacterAimDir::RightUp == AimDir)
		{
			AnimationName += "_StraightUp";
		}
		else if (CharacterAimDir::LeftDown == AimDir || CharacterAimDir::LeftDown == AimDir)
		{
			AnimationName += "_StraightDown";
		}
		else if (CharacterAimDir::Up == AimDir)
		{
			AnimationName += "_Up";
		}
		else if (CharacterAimDir::Up == AimDir)
		{
			AnimationName += "_Down";
		}
	}

	MainSpriteRenderer->ChangeAnimation(AnimationName);
}