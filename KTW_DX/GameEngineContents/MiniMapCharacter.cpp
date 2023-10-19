#include "PreCompile.h"
#include "MiniMapCharacter.h"

#include "Map.h"

MiniMapCharacter::MiniMapCharacter()
{
	GameEngineInput::AddInputObject(this);
}

MiniMapCharacter::~MiniMapCharacter()
{
}

void MiniMapCharacter::Start()
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\Texture\\MiniMapLevel");

	GameEngineFile File = Path.PlusFilePath("MiniMap_Character.png");

	GameEngineTexture::Load(File.GetStringPath());

	GameEngineSprite::CreateCut("MiniMap_Character.png", 10, 10);

	MiniCharacterRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Play);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_Up", "MiniMap_Character.png", 0.1f, 0, 3);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_Up", "MiniMap_Character.png", 0.05f, 4, 15);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_StraightUp", "MiniMap_Character.png", 0.1f, 16, 18);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_StraightUp", "MiniMap_Character.png", 0.05f, 19, 30);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_Straight", "MiniMap_Character.png", 0.1f, 31, 34);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_Straight", "MiniMap_Character.png", 0.05f, 35, 45);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_StraightDown", "MiniMap_Character.png", 0.1f, 46, 49);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_StraightDown", "MiniMap_Character.png", 0.05f, 50, 61);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_Down", "MiniMap_Character.png", 0.1f, 62, 65);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_Down", "MiniMap_Character.png", 0.05f, 66, 78);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Clear", "MiniMap_Character.png", 0.1f, 80, 88);

	MiniCharacterRenderer->AutoSpriteSizeOn();

	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _State)
			{
				IdleStart();
			};

		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				IdleUpdate(_DeltaTime);
			};
		MiniMapCharacterState.CreateState(EMINIMAPCHARACTERSTATE::Idle, Para);
	}

	{
		CreateStateParameter Para;
		Para.Start = 
			[=](GameEngineState* _State)
			{
				RunStart();
			};

		Para.Stay = 
			[=](float _DeltaTime, GameEngineState* _Parent)
			{
				RunUpdate(_DeltaTime);
			};

		MiniMapCharacterState.CreateState(EMINIMAPCHARACTERSTATE::Run, Para);
	}

	{
		CreateStateParameter Para;
		Para.Start = 
			[=](GameEngineState* _State)
			{
				ClearStart();
			};

		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				ClearUpdate(_DeltaTime);
			};
		MiniMapCharacterState.CreateState(EMINIMAPCHARACTERSTATE::Clear, Para);
	}

	MiniMapCharacterState.ChangeState(EMINIMAPCHARACTERSTATE::Idle);

	float4 CollisionScale = MINIMAPCHARACTERCOLLISIONSCALE;
	float4 CollisionPosition = { 0.0f, CollisionScale.Half().Y };

	MiniCharacterCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::Player);
	MiniCharacterCollision->Transform.SetLocalScale(CollisionScale);
	MiniCharacterCollision->Transform.SetLocalPosition(CollisionPosition);
}

void MiniMapCharacter::Update(float _Delta)
{
	float4 Pos = Transform.GetWorldPosition();
	OutputDebugStringA(Pos.ToString("\n").c_str());

	if (EACTORDIR::Left == Dir)
	{
		MiniCharacterRenderer->LeftFlip();
	}
	else
	{
		MiniCharacterRenderer->RightFlip();
	}

	MiniMapCharacterState.Update(_Delta);
}

void MiniMapCharacter::DirChange()
{
	ECHARACTERAIMDIR CheckMoveDir = ECHARACTERAIMDIR::None;

	if (true == GameEngineInput::IsPress(VK_UP, this))
	{
		CheckMoveDir = ECHARACTERAIMDIR::Up;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN, this))
	{
		CheckMoveDir = ECHARACTERAIMDIR::Down;
	}

	if (true == GameEngineInput::IsPress(VK_RIGHT, this))
	{
		Dir = EACTORDIR::Right;
		CheckMoveDir = ECHARACTERAIMDIR::Straight;
	}

	if (true == GameEngineInput::IsPress(VK_LEFT, this))
	{
		Dir = EACTORDIR::Left;
		CheckMoveDir = ECHARACTERAIMDIR::Straight;
	}

	if (true == GameEngineInput::IsPress(VK_UP, this) && true == GameEngineInput::IsPress(VK_RIGHT, this))
	{
		Dir = EACTORDIR::Right;
		CheckMoveDir = ECHARACTERAIMDIR::StraightUp;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN, this) && true == GameEngineInput::IsPress(VK_RIGHT, this))
	{
		Dir = EACTORDIR::Right;
		CheckMoveDir = ECHARACTERAIMDIR::StraightDown;
	}

	if (true == GameEngineInput::IsPress(VK_UP, this) && true == GameEngineInput::IsPress(VK_LEFT, this))
	{
		Dir = EACTORDIR::Left;
		CheckMoveDir = ECHARACTERAIMDIR::StraightUp;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN, this) && true == GameEngineInput::IsPress(VK_LEFT, this))
	{
		Dir = EACTORDIR::Left;
		CheckMoveDir = ECHARACTERAIMDIR::StraightDown;
	}

	if (CheckMoveDir != MoveDir && ECHARACTERAIMDIR::None != CheckMoveDir)
	{
		MoveDir = CheckMoveDir;
		ChangeAnimation("Run");
	}
}

void MiniMapCharacter::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "MiniCharacter_";

	AnimationName += _State;

	if ("Idle" == _State || "Run" == _State)
	{
		if (ECHARACTERAIMDIR::Up == MoveDir)
		{
			AnimationName += "_Up";
		}
		else if (ECHARACTERAIMDIR::StraightUp == MoveDir)
		{
			AnimationName += "_StraightUp";
		}
		else if (ECHARACTERAIMDIR::Straight == MoveDir)
		{
			AnimationName += "_Straight";
		}
		else if (ECHARACTERAIMDIR::StraightDown == MoveDir)
		{
			AnimationName += "_StraightDown";
		}
		else if (ECHARACTERAIMDIR::Down == MoveDir)
		{
			AnimationName += "_Down";
		}
	}

	State = _State;

	MiniCharacterRenderer->ChangeAnimation(AnimationName);
}

void MiniMapCharacter::ChangeClearState()
{
	MiniMapCharacterState.ChangeState(EMINIMAPCHARACTERSTATE::Clear);
	return;
}