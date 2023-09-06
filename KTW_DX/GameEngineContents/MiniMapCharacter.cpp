#include "PreCompile.h"
#include "MiniMapCharacter.h"

#include "Map.h"

MiniMapCharacter::MiniMapCharacter()
{
}

MiniMapCharacter::~MiniMapCharacter()
{
}

void MiniMapCharacter::Start()
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\Texture\\Character");

	GameEngineFile File = Path.PlusFilePath("MiniMap_Character.png");

	GameEngineTexture::Load(File.GetStringPath());

	GameEngineSprite::CreateCut("MiniMap_Character.png", 10, 10);

	MainSprite = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Play);
	MainSprite->CreateAnimation("MiniCharacter_Idle_Up", "MiniMap_Character.png", 0.1f, 0, 3);
	MainSprite->CreateAnimation("MiniCharacter_Run_Up", "MiniMap_Character.png", 0.05f, 4, 15);

	MainSprite->CreateAnimation("MiniCharacter_Idle_StraightUp", "MiniMap_Character.png", 0.1f, 16, 18);
	MainSprite->CreateAnimation("MiniCharacter_Run_StraightUp", "MiniMap_Character.png", 0.05f, 19, 30);

	MainSprite->CreateAnimation("MiniCharacter_Idle_Straight", "MiniMap_Character.png", 0.1f, 31, 34);
	MainSprite->CreateAnimation("MiniCharacter_Run_Straight", "MiniMap_Character.png", 0.05f, 35, 45);

	MainSprite->CreateAnimation("MiniCharacter_Idle_StraightDown", "MiniMap_Character.png", 0.1f, 46, 49);
	MainSprite->CreateAnimation("MiniCharacter_Run_StraightDown", "MiniMap_Character.png", 0.05f, 50, 61);

	MainSprite->CreateAnimation("MiniCharacter_Idle_Down", "MiniMap_Character.png", 0.1f, 62, 65);
	MainSprite->CreateAnimation("MiniCharacter_Run_Down", "MiniMap_Character.png", 0.05f, 66, 78);

	MainSprite->AutoSpriteSizeOn();

	ChangeState(MiniMapCharacterState::Idle);
}

void MiniMapCharacter::Update(float _Delta)
{
	DirChange();

	if (CharacterDir::Left == Dir)
	{
		Transform.SetLocalScale({ -1.0f, 1.0f });
	}
	else
	{
		Transform.SetLocalScale({ 1.0f, 1.0f });
	}

	StateUpdate(_Delta);
}

void MiniMapCharacter::DirChange()
{
	CharacterAimDir CheckMoveDir = CharacterAimDir::None;

	if (true == GameEngineInput::IsPress(VK_UP))
	{
		CheckMoveDir = CharacterAimDir::Up;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		CheckMoveDir = CharacterAimDir::Down;
	}

	if (true == GameEngineInput::IsPress(VK_RIGHT))
	{
		Dir = CharacterDir::Right;
		CheckMoveDir = CharacterAimDir::Straight;
	}

	if (true == GameEngineInput::IsPress(VK_LEFT))
	{
		Dir = CharacterDir::Left;
		CheckMoveDir = CharacterAimDir::Straight;
	}

	if (true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_RIGHT))
	{
		Dir = CharacterDir::Right;
		CheckMoveDir = CharacterAimDir::StraightUp;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_RIGHT))
	{
		Dir = CharacterDir::Right;
		CheckMoveDir = CharacterAimDir::StraightDown;
	}

	if (true == GameEngineInput::IsPress(VK_UP) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		Dir = CharacterDir::Left;
		CheckMoveDir = CharacterAimDir::StraightUp;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		Dir = CharacterDir::Left;
		CheckMoveDir = CharacterAimDir::StraightDown;
	}

	if (CheckMoveDir != MoveDir && CharacterAimDir::None != CheckMoveDir)
	{
		MoveDir = CheckMoveDir;
		ChangeAnimation(State);
	}
}

void MiniMapCharacter::ChangeState(MiniMapCharacterState _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case MiniMapCharacterState::Idle:
			IdleStart();
			break;
		case MiniMapCharacterState::Run:
			RunStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void MiniMapCharacter::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case MiniMapCharacterState::Idle:
		return IdleUpdate(_Delta);
	case MiniMapCharacterState::Run:
		return RunUpdate(_Delta);
	default:
		break;
	}
}

void MiniMapCharacter::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "MiniCharacter_";

	AnimationName += _State;

	if ("Idle" == _State || "Run" == _State)
	{
		if (CharacterAimDir::Up == MoveDir)
		{
			AnimationName += "_Up";
		}
		else if (CharacterAimDir::StraightUp == MoveDir)
		{
			AnimationName += "_StraightUp";
		}
		else if (CharacterAimDir::Straight == MoveDir)
		{
			AnimationName += "_Straight";
		}
		else if (CharacterAimDir::StraightDown == MoveDir)
		{
			AnimationName += "_StraightDown";
		}
		else if (CharacterAimDir::Down == MoveDir)
		{
			AnimationName += "_Down";
		}
	}

	State = _State;

	MainSprite->ChangeAnimation(AnimationName);
}