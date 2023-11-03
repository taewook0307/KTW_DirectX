#include "PreCompile.h"
#include "MiniMapCharacter.h"

#include "Map.h"
#include "MiniMapPortal.h"

MiniMapCharacter::MiniMapCharacter()
{
	GameEngineInput::AddInputObject(this);
}

MiniMapCharacter::~MiniMapCharacter()
{
}

void MiniMapCharacter::Start()
{
	MiniCharacterRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Play);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_Up", "MiniMapCharacter_Idle_Up", 0.1f, -1, -1);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_Up", "MiniMapCharacter_Run_Up", 0.05f, -1, -1);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_StraightUp", "MiniMapCharacter_Idle_StraightUp", 0.1f, -1, -1);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_StraightUp", "MiniMapCharacter_Run_StraightUp", 0.05f, -1, -1);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_Straight", "MiniMapCharacter_Idle_Straight", 0.1f, -1, -1);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_Straight", "MiniMapCharacter_Run_Straight", 0.05f, -1, -1);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_StraightDown", "MiniMapCharacter_Idle_StraightDown", 0.1f, -1, -1);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_StraightDown", "MiniMapCharacter_Run_StraightDown", 0.05f, -1, -1);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Idle_Down", "MiniMapCharacter_Idle_Down", 0.1f, -1, -1);
	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Run_Down", "MiniMapCharacter_Run_Down", 0.05f, -1, -1);

	MiniCharacterRenderer->CreateAnimation("MiniCharacter_Clear", "MiniMapCharacter_Win", 0.1f, -1, -1);

	MiniCharacterRenderer->AutoSpriteSizeOn();
	MiniCharacterRenderer->SetPivotType(PivotType::Bottom);

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
	PortalEventParaSetting();
}

void MiniMapCharacter::Update(float _Delta)
{
	float4 Pos = Transform.GetWorldPosition();
	OutputDebugStringA(Pos.ToString().c_str());

	if (EACTORDIR::Left == Dir)
	{
		MiniCharacterRenderer->LeftFlip();
	}
	else
	{
		MiniCharacterRenderer->RightFlip();
	}

	MiniCharacterCollision->CollisionEvent(ECOLLISIONORDER::Portal, PortalPara);

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

void MiniMapCharacter::PortalEventParaSetting()
{
	PortalPara.Enter = [&](GameEngineCollision* _This, GameEngineCollision* _Collisions)
		{
			GameEngineActor* Other = _Collisions->GetActor();
			CurPortal = dynamic_cast<MiniMapPortal*>(Other);
		};

	PortalPara.Stay = [&](GameEngineCollision* _This, GameEngineCollision* _Collisions)
		{
			if (nullptr == PrevPortal)
			{
				if (nullptr == CurPortal)
				{
					MsgBoxAssert("포탈이 아닙니다");
					return;
				}

				float4 Pos = CurPortal->GetDestination();

				GameEngineActor* Character = _This->GetActor();
				Character->Transform.SetLocalPosition(Pos);
				PrevPortal = CurPortal;
			}
			else if (PrevPortal == CurPortal)
			{
				if (nullptr == CurPortal)
				{
					MsgBoxAssert("포탈이 아닙니다");
					return;
				}

				float4 Pos = CurPortal->GetDestination();

				GameEngineActor* Character = _This->GetActor();
				Character->Transform.SetLocalPosition(Pos);
			}
		};
	PortalPara.Exit = [&](GameEngineCollision* _This, GameEngineCollision* _Collisions)
		{
			PrevPortal = CurPortal;
		};
}