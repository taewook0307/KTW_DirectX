#include "PreCompile.h"
#include "WorldMapCharacter.h"

#include "Map.h"

void WorldMapCharacter::IdleStart(GameEngineState* _State)
{
	ChangeAnimation("Idle");
}

void WorldMapCharacter::IdleUpdate(float _Delta, GameEngineState* _State)
{
	if (
		true == GameEngineInput::IsPress(VK_LEFT, this)
		|| true == GameEngineInput::IsPress(VK_RIGHT, this)
		|| true == GameEngineInput::IsPress(VK_UP, this)
		|| true == GameEngineInput::IsPress(VK_DOWN, this)
		)
	{
		WorldMapCharacterState.ChangeState(EWORLDMAPCHARACTERSTATE::Run);
		return;
	}
}

void WorldMapCharacter::RunStart(GameEngineState* _State)
{
	ChangeAnimation("Run");
}

void WorldMapCharacter::RunUpdate(float _Delta, GameEngineState* _State)
{
	int CurIndex = WorldCharacterRenderer->CurAnimation()->CurIndex;
	if (2 == CurIndex || 10 == CurIndex)
	{
		RunSoundPlayer.RandomSoundPlay();
		CreateRunDust();
	}

	DirChange();

	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (GameEngineInput::IsPress(VK_UP, this))
	{
		MovePos += float4::UP * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		MovePos += float4::DOWN * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_LEFT, this))
	{
		MovePos += float4::LEFT * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_RIGHT, this))
	{
		MovePos += float4::RIGHT * _Delta * Speed;
	}

	if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::Straight == MoveDir)
	{
		CheckPos = { -20.0f, 40.0f };
	}

	if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::Straight == MoveDir)
	{
		CheckPos = { 20.0f, 40.0f };
	}

	if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::StraightDown == MoveDir)
	{
		CheckPos = { -20.0f, 0.0f };
	}

	if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::StraightDown == MoveDir)
	{
		CheckPos = { 20.0f, 0.0f };
	}

	if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::StraightUp == MoveDir)
	{
		CheckPos = { -20.0f, 80.0f };
	}

	if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::StraightUp == MoveDir)
	{
		CheckPos = { 20.0f, 80.0f };
	}

	if (ECHARACTERAIMDIR::Up == MoveDir)
	{
		CheckPos = { 0.0f, 80.0f };
	}

	CheckPos += Transform.GetWorldPosition();

	if (Map::MainMap->GetColor(CheckPos, FLOORCOLOR) != FLOORCOLOR)
	{
		Transform.AddLocalPosition(MovePos);
	}

	if (float4::ZERO == MovePos)
	{
		WorldMapCharacterState.ChangeState(EWORLDMAPCHARACTERSTATE::Idle);
		return;
	}
}

void WorldMapCharacter::ClearStart(GameEngineState* _State)
{
	ChangeAnimation("Clear");
}

void WorldMapCharacter::ClearUpdate(float _Delta, GameEngineState* _State)
{
	if (true == WorldCharacterRenderer->IsCurAnimationEnd())
	{
		--ClearLoopCount;
	}

	if (0 >= ClearLoopCount)
	{
		ClearLoopCount = CLEARLOOPCOUNT;
		WorldMapCharacterState.ChangeState(EWORLDMAPCHARACTERSTATE::Idle);
		return;
	}
}