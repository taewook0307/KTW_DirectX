#include "PreCompile.h"
#include "WorldMapCharacter.h"

#include "Map.h"
#include "WorldMapPortal.h"

#include "FadeObject.h"

WorldMapCharacter::WorldMapCharacter()
{
	GameEngineInput::AddInputObject(this);
}

WorldMapCharacter::~WorldMapCharacter()
{
}

void WorldMapCharacter::Start()
{
	WorldCharacterRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Play);
	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Idle_Up", "WorldMapCharacter_Idle_Up", 0.1f, -1, -1);
	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Run_Up", "WorldMapCharacter_Run_Up", 0.05f, -1, -1);

	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Idle_StraightUp", "WorldMapCharacter_Idle_StraightUp", 0.1f, -1, -1);
	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Run_StraightUp", "WorldMapCharacter_Run_StraightUp", 0.05f, -1, -1);

	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Idle_Straight", "WorldMapCharacter_Idle_Straight", 0.1f, -1, -1);
	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Run_Straight", "WorldMapCharacter_Run_Straight", 0.05f, -1, -1);

	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Idle_StraightDown", "WorldMapCharacter_Idle_StraightDown", 0.1f, -1, -1);
	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Run_StraightDown", "WorldMapCharacter_Run_StraightDown", 0.05f, -1, -1);

	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Idle_Down", "WorldMapCharacter_Idle_Down", 0.1f, -1, -1);
	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Run_Down", "WorldMapCharacter_Run_Down", 0.05f, -1, -1);

	WorldCharacterRenderer->CreateAnimation("WorldCharacter_Clear", "WorldMapCharacter_Win", 0.1f, -1, -1);
																 
	WorldCharacterRenderer->AutoSpriteSizeOn();
	WorldCharacterRenderer->SetPivotType(PivotType::Bottom);

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
		WorldMapCharacterState.CreateState(EWORLDMAPCHARACTERSTATE::Idle, Para);
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

		WorldMapCharacterState.CreateState(EWORLDMAPCHARACTERSTATE::Run, Para);
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
		WorldMapCharacterState.CreateState(EWORLDMAPCHARACTERSTATE::Clear, Para);
	}

	WorldMapCharacterState.ChangeState(EWORLDMAPCHARACTERSTATE::Idle);

	float4 CollisionScale = MINIMAPCHARACTERCOLLISIONSCALE;
	float4 CollisionPosition = { 0.0f, CollisionScale.Half().Y };

	WorldCharacterCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::Player);
	WorldCharacterCollision->Transform.SetLocalScale(CollisionScale);
	WorldCharacterCollision->Transform.SetLocalPosition(CollisionPosition);
	PortalEventParaSetting();
}

void WorldMapCharacter::Update(float _Delta)
{
	float4 Pos = Transform.GetWorldPosition();
	OutputDebugStringA(Pos.ToString().c_str());

	if (EACTORDIR::Left == Dir)
	{
		WorldCharacterRenderer->LeftFlip();
	}
	else
	{
		WorldCharacterRenderer->RightFlip();
	}

	WorldCharacterCollision->CollisionEvent(ECOLLISIONORDER::Portal, PortalPara);

	WorldMapCharacterState.Update(_Delta);
}

void WorldMapCharacter::DirChange()
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

void WorldMapCharacter::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "WorldCharacter_";

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

	WorldCharacterRenderer->ChangeAnimation(AnimationName);
}

void WorldMapCharacter::ChangeClearState()
{
	WorldMapCharacterState.ChangeState(EWORLDMAPCHARACTERSTATE::Clear);
	return;
}

void WorldMapCharacter::PortalEventParaSetting()
{
	PortalPara.Enter = [&](GameEngineCollision* _This, GameEngineCollision* _Collisions)
		{
			GameEngineActor* Other = _Collisions->GetActor();
			CurPortal = dynamic_cast<WorldMapPortal*>(Other);
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