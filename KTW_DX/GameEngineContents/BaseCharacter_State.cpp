#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"

void BaseCharacter::IdleStart()
{
	ChangeAnimation("Idle");
}

void BaseCharacter::IdleUpdate(float _Delta)
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (CheckColor != GameEngineColor::RED)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
	}

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
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (CheckColor != GameEngineColor::RED)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
	}
	
	float4 MovePos = float4::ZERO;

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		MovePos = float4::LEFT * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_RIGHT))
	{
		MovePos = float4::RIGHT * _Delta * Speed;
	}

	Transform.AddLocalPosition(MovePos);

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
	GameEngineColor CheckColor;

	if (GetGravityForce().Y > 0)
	{
		CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition() + float4 {0.0f, 80.0f}, GameEngineColor::RED);
	}
	else
	{
		CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);
	}

	if (CheckColor != GameEngineColor::RED)
	{
		GravityOn(_Delta);
	}
	else
	{
		GravityReset();
	}

	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED == Color)
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
	Transform.AddLocalPosition(float4::RIGHT * DashSpeed * _Delta);

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(CharacterState::Idle);
	}
}