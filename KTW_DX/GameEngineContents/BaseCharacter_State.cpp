#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"


void BaseCharacter::CharacterMove(float _Delta)
{
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
}

void BaseCharacter::CharacterGravity(float _Delta, float4 _CheckPos)
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(_CheckPos, FLOORCOLOR);

	if (false == StoolPass)
	{
		if (FLOORCOLOR != CheckColor && STOOLCOLOR != CheckColor)
		{
			GravityOn(_Delta);
		}
		else
		{
			GravityReset();
		}
	}
	else
	{
		if (FLOORCOLOR != CheckColor)
		{
			GravityOn(_Delta);
		}
		else
		{
			GravityReset();
			StoolPass = false;
		}
	}
}

void BaseCharacter::IntroStart()
{
	ChangeAnimation("Intro");
}

void BaseCharacter::IntroUpdate(float _Delta)
{
	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	if (true == PlayerRenderer->IsCurAnimationEnd())
	{
		ChangeState(CharacterState::Idle);
		return;
	}
}

void BaseCharacter::IdleStart()
{
	ChangeAnimation("Idle");
}

void BaseCharacter::IdleUpdate(float _Delta)
{
	DirChange();

	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	// Change State
	if (true == GameEngineInput::IsPress(VK_LEFT) && true == GameEngineInput::IsPress('X')
		|| true == GameEngineInput::IsPress(VK_RIGHT) && true == GameEngineInput::IsPress('X'))
	{
		ChangeState(CharacterState::RunShoot);
		return;
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

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(CharacterState::Aim);
		return;
	}

	if (true == GameEngineInput::IsPress('X'))
	{
		ChangeState(CharacterState::Shoot);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeState(CharacterState::Duck);
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
	CharacterGravity(_Delta, Transform.GetWorldPosition());
	
	// Move
	CharacterMove(_Delta);

	// Change State
	if (true == GameEngineInput::IsFree(VK_LEFT)
		&& true == GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(CharacterState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(CharacterState::Dash);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(CharacterState::RunShoot);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(CharacterState::Jump);
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
	ShootAimState();

	// Gravity
	if (GetGravityForce().Y > 0)
	{
		StoolPass = true;
		CharacterGravity(_Delta, Transform.GetWorldPosition() + float4{ 0.0f, 80.0f });
	}
	else
	{
		StoolPass = false;
		CharacterGravity(_Delta, Transform.GetWorldPosition());
	}

	//Move
	CharacterMove(_Delta);

	// Change State
	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == Color || (STOOLCOLOR == Color && false == StoolPass))
	{
		ChangeState(CharacterState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(CharacterState::Parry);
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
	GravityReset();
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		ChangeAnimation("Dash_Air");
	}
	else
	{
		ChangeAnimation("Dash");
	}
}

void BaseCharacter::DashUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (CharacterDir::Right == Dir)
	{
		MovePos = float4::RIGHT * DashSpeed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}
	else if (CharacterDir::Left == Dir)
	{
		MovePos = float4::LEFT * DashSpeed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}

	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition() + CheckPos, FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		Transform.AddLocalPosition(MovePos);
	}


	if (true == PlayerRenderer->IsCurAnimationEnd())
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
	DirChange();

	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	if (0 == GetGravityForce().Y)
	{
		ChangeState(CharacterState::Idle);
		return;
	}

	// Move
	CharacterMove(_Delta);
}

void BaseCharacter::DuckStart()
{
	ChangeAnimation("Duck");
}

void BaseCharacter::DuckUpdate(float _Delta)
{
	DirChange();
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	if (true == PlayerRenderer->IsCurAnimationEnd() && true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeAnimation("Duck_Idle");
	}
	
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (STOOLCOLOR == CheckColor)
	{
		if (true == GameEngineInput::IsPress(VK_DOWN) && true == GameEngineInput::IsDown('Z'))
		{
			ChangeAnimation("Fall");
			StoolPass = true;
		}
	}

	if (true == GameEngineInput::IsPress('X'))
	{
		ChangeState(CharacterState::DuckShoot);
		return;
	}

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeState(CharacterState::Idle);
		return;
	}
}

void BaseCharacter::ParryStart()
{
	ChangeAnimation("Parry");
}

void BaseCharacter::ParryUpdate(float _Delta)
{
	DirChange();

	// Gravity
	if (GetGravityForce().Y > 0)
	{
		CharacterGravity(_Delta, Transform.GetWorldPosition() + float4{ 0.0f, 80.0f });
	}
	else
	{
		CharacterGravity(_Delta, Transform.GetWorldPosition());
	}

	//Move
	CharacterMove(_Delta);
}