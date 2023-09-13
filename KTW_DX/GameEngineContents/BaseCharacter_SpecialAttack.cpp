#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"
#include "SpecialBullet.h"


void BaseCharacter::SpecialShootState()
{
	std::shared_ptr<SpecialBullet> NewBullet = GetLevel()->CreateActor<SpecialBullet>(UpdateOrder::Bullet);
	float4 NewBulletPos = float4::ZERO;

	// 왼쪽
	if (CharacterDir::Left == Dir && CharacterAimDir::Straight == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ -80.0f, 40.0f };
		NewBullet->SetBulletDir(BulletDirection::Left);
	}

	// 오른쪽
	else if (CharacterDir::Right == Dir && CharacterAimDir::Straight == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ 80.0f, 40.0f };
		NewBullet->SetBulletDir(BulletDirection::Right);
	}

	// 위
	else if (CharacterAimDir::Up == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ 0.0f, 130.0f };
		NewBullet->SetBulletDir(BulletDirection::Up);
	}

	// 아래
	else if (CharacterAimDir::Down == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ 0.0f, 00.0f };
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
}

void BaseCharacter::SpecialAttackStart()
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		ChangeAnimation("SpecialAttack_Air");
	}
	else
	{
		ChangeAnimation("SpecialAttack");
	}
}

void BaseCharacter::SpecialAttackUpdate(float _Delta)
{
	if (true == Cheat)
	{
		SpecialShootState();
	}

	if (true == PlayerRenderer->IsCurAnimationEnd() && false == Cheat)
	{
		GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

		if (CheckColor != FLOORCOLOR)
		{
			ChangeState(CharacterState::Fall);
			return;
		}
		else
		{
			ChangeState(CharacterState::Idle);
			return;
		}
	}

	if (true == Cheat && true == PlayerRenderer->IsCurAnimationEnd() && true == GameEngineInput::IsFree('V'))
	{
		GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

		if (CheckColor != FLOORCOLOR)
		{
			ChangeState(CharacterState::Fall);
			return;
		}
		else
		{
			ChangeState(CharacterState::Idle);
			return;
		}
	}
}