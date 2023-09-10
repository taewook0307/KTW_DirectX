#include "PreCompile.h"
#include "BaseCharacter.h"

void BaseCharacter::ShootStart()
{
	ChangeAnimation("Shoot");
}

void BaseCharacter::ShootUpdate(float _Delta)
{
	DirChange();

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(CharacterState::Idle);
		return;
	}

	if(true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(CharacterState::RunShoot);
		return;
	}
}

void BaseCharacter::AimStart()
{
	ChangeAnimation("Aim");
}

void BaseCharacter::AimUpdate(float _Delta)
{
	DirChange();

	if (true == GameEngineInput::IsFree('C'))
	{
		ChangeState(CharacterState::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress('X'))
	{
		ChangeState(CharacterState::AimShoot);
		return;
	}
}

void BaseCharacter::AimShootStart()
{
	ChangeAnimation("AimShoot");
}

void BaseCharacter::AimShootUpdate(float _Delta)
{
	DirChange();

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(CharacterState::Jump);
		return;
	}

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(CharacterState::Aim);
		return;
	}

	if (true == GameEngineInput::IsFree('C'))
	{
		ChangeState(CharacterState::Shoot);
		return;
	}
}

void BaseCharacter::RunShootStart()
{
	ChangeAnimation("RunShoot");
}

void BaseCharacter::RunShootUpdate(float _Delta)
{
	DirChange();

	// Move
	CharacterMove(_Delta);

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(CharacterState::Run);
		return;
	}

	if (true == GameEngineInput::IsFree(VK_LEFT)
		&& true == GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(CharacterState::Shoot);
		return;
	}
}