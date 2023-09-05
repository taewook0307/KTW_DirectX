#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"

void BaseCharacter::IdleStart()
{
	ChangeAnimation("Idle");
}

void BaseCharacter::IdleUpdate(float _Delta)
{
	DirChange();

	// Gravity
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
	}

	// Change State
	if (true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(CharacterState::Run);
		return;
	}

	if (true == GameEngineInput::IsPress('Z'))
	{
		ChangeState(CharacterState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(CharacterState::Dash);
		return;
	}
}

void BaseCharacter::RunStart()
{
	ChangeAnimation("Run");
}

void BaseCharacter::RunUpdate(float _Delta)
{
	DirChange();

	// Gravity
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
	}
	
	// Move
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		MovePos = float4::LEFT * _Delta * Speed;
		CheckPos = LEFTCHECKPOS;
	}

	if (GameEngineInput::IsPress(VK_RIGHT))
	{
		MovePos = float4::RIGHT * _Delta * Speed;
		CheckPos = RIGHTCHECKPOS;
	}

	GameEngineColor MoveCheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition() + CheckPos, FLOORCOLOR);

	if (FLOORCOLOR != MoveCheckColor)
	{
		Transform.AddLocalPosition(MovePos);
	}

	// Change State
	if (float4::ZERO == MovePos)
	{
		ChangeState(CharacterState::Idle);
		return;
	}
}

void BaseCharacter::JumpStart()
{
	SetGravityForce(float4::UP * JUMPPOWER);
	ChangeAnimation("Jump");
}

void BaseCharacter::JumpUpdate(float _Delta)
{
	DirChange();

	// Gravity
	GameEngineColor CheckColor;

	if (GetGravityForce().Y > 0)
	{
		CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition() + float4 {0.0f, 80.0f}, FLOORCOLOR);
	}
	else
	{
		CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);
	}

	if (CheckColor != FLOORCOLOR)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
	}

	// Change State
	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == Color)
	{
		ChangeState(CharacterState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(CharacterState::Dash);
		return;
	}
}

void BaseCharacter::DashStart()
{
	ChangeAnimation("Dash");
}

void BaseCharacter::DashUpdate(float _Delta)
{
	if (CharacterDir::Right == Dir)
	{
		Transform.AddLocalPosition(float4::RIGHT * DashSpeed * _Delta);
	}
	else if (CharacterDir::Left == Dir)
	{
		Transform.AddLocalPosition(float4::LEFT * DashSpeed * _Delta);
	}

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(CharacterState::Fall);
		return;
	}
}

void BaseCharacter::FallStart()
{
	ChangeAnimation("Fall");
}

void BaseCharacter::FallUpdate(float _Delta)
{
	// Gravity
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(CharacterState::Idle);
		return;
	}

	// Move
	GameEngineColor MoveCheck = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);
}