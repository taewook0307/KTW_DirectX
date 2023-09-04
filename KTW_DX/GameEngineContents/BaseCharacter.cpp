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
	MainSpriteRenderer->SetAutoScaleRatio(0.8f);
	MainSpriteRenderer->CreateAnimation("CupHead_Idle", "Idle");
	MainSpriteRenderer->CreateAnimation("CupHead_Run", "Run");
	MainSpriteRenderer->CreateAnimation("CupHead_Jump", "Jump", 0.08f);
	MainSpriteRenderer->ChangeAnimation("CupHead_Idle");
	MainSpriteRenderer->AutoSpriteSizeOn();
}

void BaseCharacter::Update(float _Delta)
{
	StateUpdate(_Delta);
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

	MainSpriteRenderer->ChangeAnimation(AnimationName);
}