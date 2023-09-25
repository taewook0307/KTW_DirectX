#include "PreCompile.h"
#include "MiniMapCharacter.h"

#include "Map.h"

void MiniMapCharacter::IdleStart()
{
	ChangeAnimation("Idle");
}

void MiniMapCharacter::IdleUpdate(float _Delta)
{
	if (
		true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_UP)
		|| true == GameEngineInput::IsPress(VK_DOWN)
		)
	{
		ChangeState(EMINIMAPCHARACTERSTATE::Run);
		return;
	}
}

void MiniMapCharacter::RunStart()
{
	ChangeAnimation("Run");
}

void MiniMapCharacter::RunUpdate(float _Delta)
{
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (GameEngineInput::IsPress(VK_UP))
	{
		MovePos += float4::UP * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_DOWN))
	{
		MovePos += float4::DOWN * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		MovePos += float4::LEFT * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_RIGHT))
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
		ChangeState(EMINIMAPCHARACTERSTATE::Idle);
		return;
	}
}