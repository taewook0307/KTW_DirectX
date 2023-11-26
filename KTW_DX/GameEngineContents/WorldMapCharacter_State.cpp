#include "PreCompile.h"
#include "WorldMapCharacter.h"

#include "Map.h"

void WorldMapCharacter::IdleStart()
{
	ChangeAnimation("Idle");
}

void WorldMapCharacter::IdleUpdate(float _Delta)
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

void WorldMapCharacter::RunStart()
{
	ChangeAnimation("Run");
}

void WorldMapCharacter::RunUpdate(float _Delta)
{
	int CurIndex = WorldCharacterRenderer->CurAnimation()->CurIndex;
	if (2 == CurIndex || 10 == CurIndex)
	{
		
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

void WorldMapCharacter::ClearStart()
{
	ChangeAnimation("Clear");
}

void WorldMapCharacter::ClearUpdate(float _Delta)
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