#include "PreCompile.h"
#include "BaseCharacter.h"

void BaseCharacter::IdleStart()
{
	ChangeAnimation("Idle");
}

void BaseCharacter::IdleUpdate(float _Delta)
{
	GravityOn(_Delta);

	if (true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(CharacterState::Run);
	}

	if (true == GameEngineInput::IsPress('Z'))
	{
		ChangeState(CharacterState::Jump);
	}
}

void BaseCharacter::RunStart()
{
	ChangeAnimation("Run");
}

void BaseCharacter::RunUpdate(float _Delta)
{
	GravityOn(_Delta);

	float Speed = 300.0f;
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
	}
}

void BaseCharacter::JumpStart()
{
	ChangeAnimation("Jump");
}

void BaseCharacter::JumpUpdate(float _Delta)
{

}