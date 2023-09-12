#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"
#include "Bullet.h"

void BaseCharacter::ShootBaseState()
{
	if (true == GameEngineInput::IsDown('X') || true == GameEngineInput::IsPress('X'))
	{
		if (false == Shoot)
		{
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(UpdateOrder::Bullet);
			float4 NewBulletPos = float4::ZERO;

			// 왼쪽
			if (CharacterDir::Left == Dir)
			{
				// 위(왼쪽)
				if (CharacterAimDir::Up == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -30.0f, 130.0f };
					NewBullet->SetBulletDir(BulletDirection::Up);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 60.0f };
					NewBullet->SetBulletDir(BulletDirection::Left);
				}
			}
			else
			{
				// 위(오른쪽)
				if (CharacterAimDir::Up == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 30.0f, 130.0f };
					NewBullet->SetBulletDir(BulletDirection::Up);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 60.0f };
					NewBullet->SetBulletDir(BulletDirection::Right);
				}
			}

			NewBullet->Transform.SetLocalPosition(NewBulletPos);
			Shoot = true;
		}
	}
}

void BaseCharacter::ShootAimState()
{
	if (true == GameEngineInput::IsDown('X') || true == GameEngineInput::IsPress('X'))
	{
		if (false == Shoot)
		{
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(UpdateOrder::Bullet);
			float4 NewBulletPos = float4::ZERO;

			// 왼쪽
			if (CharacterDir::Left == Dir && CharacterAimDir::Straight == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 60.0f };
				NewBullet->SetBulletDir(BulletDirection::Left);
			}

			// 오른쪽
			else if (CharacterDir::Right == Dir && CharacterAimDir::Straight == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 60.0f };
				NewBullet->SetBulletDir(BulletDirection::Right);
			}

			// 위(왼쪽)
			else if (CharacterDir::Left == Dir && CharacterAimDir::Up == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -30.0f, 130.0f };
				NewBullet->SetBulletDir(BulletDirection::Up);
			}

			// 아래(왼쪽)
			else if (CharacterDir::Left == Dir && CharacterAimDir::Down == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -20.0f, 00.0f };
				NewBullet->SetBulletDir(BulletDirection::Down);
			}

			// 위(오른쪽)
			else if (CharacterDir::Right == Dir && CharacterAimDir::Up == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 30.0f, 130.0f };
				NewBullet->SetBulletDir(BulletDirection::Up);
			}

			// 아래(오른쪽)
			else if (CharacterDir::Right == Dir && CharacterAimDir::Down == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 20.0f, 00.0f };
				NewBullet->SetBulletDir(BulletDirection::Down);
			}

			// 왼쪽 위
			else if (CharacterDir::Left == Dir && CharacterAimDir::StraightUp == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 110.0f };
				NewBullet->SetBulletDir(BulletDirection::LeftUp);
			}

			// 왼쪽 아래
			else if (CharacterDir::Left == Dir && CharacterAimDir::StraightDown == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 20.0f };
				NewBullet->SetBulletDir(BulletDirection::LeftDown);
			}

			// 오른쪽 위
			else if (CharacterDir::Right == Dir && CharacterAimDir::StraightUp == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 110.0f };
				NewBullet->SetBulletDir(BulletDirection::RightUp);
			}

			// 오른쪽 아래
			else if (CharacterDir::Right == Dir && CharacterAimDir::StraightDown == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 20.0f };
				NewBullet->SetBulletDir(BulletDirection::RightDown);
			}

			NewBullet->Transform.SetLocalPosition(NewBulletPos);
			Shoot = true;
		}
	}
}

void BaseCharacter::ShootRunState()
{
	if (true == GameEngineInput::IsDown('X') || true == GameEngineInput::IsPress('X'))
	{
		if (false == Shoot)
		{
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(UpdateOrder::Bullet);
			float4 NewBulletPos = float4::ZERO;

			if (CharacterDir::Left == Dir)
			{
				// 왼쪽 위
				if (CharacterAimDir::StraightUp == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -60.0f, 110.0f };
					NewBullet->SetBulletDir(BulletDirection::LeftUp);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -60.0f, 50.0f };
					NewBullet->SetBulletDir(BulletDirection::Left);
				}
			}
			else
			{
				// 오른쪽 위
				if (CharacterDir::Right == Dir && CharacterAimDir::StraightUp == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 60.0f, 110.0f };
					NewBullet->SetBulletDir(BulletDirection::RightUp);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 60.0f, 50.0f };
					NewBullet->SetBulletDir(BulletDirection::Right);
				}
			}
			
			NewBullet->Transform.SetLocalPosition(NewBulletPos);
			Shoot = true;
		}
	}
}

void BaseCharacter::ShootDuckState()
{
	if (true == GameEngineInput::IsDown('X') || true == GameEngineInput::IsPress('X'))
	{
		if (false == Shoot)
		{
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(UpdateOrder::Bullet);
			float4 NewBulletPos = float4::ZERO;

			// 왼쪽
			if (CharacterDir::Left == Dir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -70.0f, 30.0f };
				NewBullet->SetBulletDir(BulletDirection::Left);
			}

			// 오른쪽
			else if (CharacterDir::Right == Dir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 70.0f, 30.0f };
				NewBullet->SetBulletDir(BulletDirection::Right);
			}

			NewBullet->Transform.SetLocalPosition(NewBulletPos);
			Shoot = true;
		}
	}
}



void BaseCharacter::ShootStart()
{
	ChangeAnimation("Shoot");
}

void BaseCharacter::ShootUpdate(float _Delta)
{
	DirChange();

	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	ShootBaseState();

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

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeState(CharacterState::Duck);
		return;
	}

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(CharacterState::AimShoot);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(CharacterState::Jump);
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

	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

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

	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	ShootAimState();

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

	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	ShootRunState();

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

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(CharacterState::Jump);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeState(CharacterState::DuckShoot);
		return;
	}
}

void BaseCharacter::DuckShootStart()
{
	ChangeAnimation("DuckShoot");
}

void BaseCharacter::DuckShootUpdate(float _Delta)
{
	DirChange();

	// Gravity
	CharacterGravity(_Delta, Transform.GetWorldPosition());

	ShootDuckState();

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeState(CharacterState::Shoot);
		return;
	}

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(CharacterState::Duck);
		return;
	}
}