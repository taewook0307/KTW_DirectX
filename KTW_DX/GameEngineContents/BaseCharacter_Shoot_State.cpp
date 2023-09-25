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
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(EUPDATEORDER::Bullet);
			float4 NewBulletPos = float4::ZERO;

			// 왼쪽
			if (EACTORDIR::Left == Dir)
			{
				// 위(왼쪽)
				if (ECHARACTERAIMDIR::Up == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -30.0f, 130.0f };
					NewBullet->SetBulletDir(EDIRECTION8::Up);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 60.0f };
					NewBullet->SetBulletDir(EDIRECTION8::Left);
				}
			}
			else
			{
				// 위(오른쪽)
				if (ECHARACTERAIMDIR::Up == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 30.0f, 130.0f };
					NewBullet->SetBulletDir(EDIRECTION8::Up);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 60.0f };
					NewBullet->SetBulletDir(EDIRECTION8::Right);
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
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(EUPDATEORDER::Bullet);
			float4 NewBulletPos = float4::ZERO;

			// 왼쪽
			if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::Straight == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 60.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Left);
			}

			// 오른쪽
			else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::Straight == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 60.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Right);
			}

			// 위(왼쪽)
			else if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::Up == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -30.0f, 130.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Up);
			}

			// 아래(왼쪽)
			else if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::Down == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -20.0f, 00.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Down);
			}

			// 위(오른쪽)
			else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::Up == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 30.0f, 130.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Up);
			}

			// 아래(오른쪽)
			else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::Down == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 20.0f, 00.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Down);
			}

			// 왼쪽 위
			else if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::StraightUp == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 110.0f };
				NewBullet->SetBulletDir(EDIRECTION8::LeftUp);
			}

			// 왼쪽 아래
			else if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::StraightDown == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 20.0f };
				NewBullet->SetBulletDir(EDIRECTION8::LeftDown);
			}

			// 오른쪽 위
			else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::StraightUp == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 110.0f };
				NewBullet->SetBulletDir(EDIRECTION8::RightUp);
			}

			// 오른쪽 아래
			else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::StraightDown == AimDir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 20.0f };
				NewBullet->SetBulletDir(EDIRECTION8::RightDown);
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
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(EUPDATEORDER::Bullet);
			float4 NewBulletPos = float4::ZERO;

			if (EACTORDIR::Left == Dir)
			{
				// 왼쪽 위
				if (ECHARACTERAIMDIR::StraightUp == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -60.0f, 110.0f };
					NewBullet->SetBulletDir(EDIRECTION8::LeftUp);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ -60.0f, 50.0f };
					NewBullet->SetBulletDir(EDIRECTION8::Left);
				}
			}
			else
			{
				// 오른쪽 위
				if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::StraightUp == AimDir)
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 60.0f, 110.0f };
					NewBullet->SetBulletDir(EDIRECTION8::RightUp);
				}

				else
				{
					NewBulletPos = Transform.GetWorldPosition() + float4{ 60.0f, 50.0f };
					NewBullet->SetBulletDir(EDIRECTION8::Right);
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
			std::shared_ptr<Bullet> NewBullet = GetLevel()->CreateActor<Bullet>(EUPDATEORDER::Bullet);
			float4 NewBulletPos = float4::ZERO;

			// 왼쪽
			if (EACTORDIR::Left == Dir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ -70.0f, 30.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Left);
			}

			// 오른쪽
			else if (EACTORDIR::Right == Dir)
			{
				NewBulletPos = Transform.GetWorldPosition() + float4{ 70.0f, 30.0f };
				NewBullet->SetBulletDir(EDIRECTION8::Right);
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
	ActorGravity(_Delta, Transform.GetWorldPosition());

	ShootBaseState();

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(ECHARACTERSTATE::Idle);
		return;
	}

	if(true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(ECHARACTERSTATE::RunShoot);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeState(ECHARACTERSTATE::Duck);
		return;
	}

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(ECHARACTERSTATE::AimShoot);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(ECHARACTERSTATE::Jump);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		ChangeState(ECHARACTERSTATE::Dash);
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
	ActorGravity(_Delta, Transform.GetWorldPosition());

	if (true == GameEngineInput::IsFree('C'))
	{
		ChangeState(ECHARACTERSTATE::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress('X'))
	{
		ChangeState(ECHARACTERSTATE::AimShoot);
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
	ActorGravity(_Delta, Transform.GetWorldPosition());

	ShootAimState();

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(ECHARACTERSTATE::Jump);
		return;
	}

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(ECHARACTERSTATE::Aim);
		return;
	}

	if (true == GameEngineInput::IsFree('C'))
	{
		ChangeState(ECHARACTERSTATE::Shoot);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		ChangeState(ECHARACTERSTATE::Dash);
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
	ActorGravity(_Delta, Transform.GetWorldPosition());

	ShootRunState();

	// Move
	CharacterMove(_Delta);

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(ECHARACTERSTATE::Run);
		return;
	}

	if (true == GameEngineInput::IsFree(VK_LEFT)
		&& true == GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(ECHARACTERSTATE::Shoot);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(ECHARACTERSTATE::Jump);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeState(ECHARACTERSTATE::DuckShoot);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		ChangeState(ECHARACTERSTATE::Dash);
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
	ActorGravity(_Delta, Transform.GetWorldPosition());

	ShootDuckState();

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeState(ECHARACTERSTATE::Shoot);
		return;
	}

	if (true == GameEngineInput::IsFree('X'))
	{
		ChangeState(ECHARACTERSTATE::Duck);
		return;
	}
}