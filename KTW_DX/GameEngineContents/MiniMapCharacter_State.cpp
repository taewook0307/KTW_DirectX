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
		ChangeState(MiniMapCharacterState::Run);
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

	if (ActorDir::Left == Dir && CharacterAimDir::Straight == MoveDir)
	{
		CheckPos = { -20.0f, 40.0f };
	}

	if (ActorDir::Right == Dir && CharacterAimDir::Straight == MoveDir)
	{
		CheckPos = { 20.0f, 40.0f };
	}

	if (ActorDir::Left == Dir && CharacterAimDir::StraightDown == MoveDir)
	{
		CheckPos = { -20.0f, 0.0f };
	}

	if (ActorDir::Right == Dir && CharacterAimDir::StraightDown == MoveDir)
	{
		CheckPos = { 20.0f, 0.0f };
	}

	if (ActorDir::Left == Dir && CharacterAimDir::StraightUp == MoveDir)
	{
		CheckPos = { -20.0f, 80.0f };
	}

	if (ActorDir::Right == Dir && CharacterAimDir::StraightUp == MoveDir)
	{
		CheckPos = { 20.0f, 80.0f };
	}

	if (CharacterAimDir::Up == MoveDir)
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
		ChangeState(MiniMapCharacterState::Idle);
		return;
	}
}