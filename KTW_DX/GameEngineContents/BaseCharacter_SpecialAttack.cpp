#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"
#include "SpecialBullet.h"


void BaseCharacter::SpecialShootState()
{
	std::shared_ptr<SpecialBullet> NewBullet = GetLevel()->CreateActor<SpecialBullet>(UpdateOrder::Bullet);
	float4 NewBulletPos = float4::ZERO;

	// ����
	if (ActorDir::Left == Dir && CharacterAimDir::Straight == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ -80.0f, 40.0f };
		NewBullet->SetBulletDir(Direction8::Left);
	}

	// ������
	else if (ActorDir::Right == Dir && CharacterAimDir::Straight == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ 80.0f, 40.0f };
		NewBullet->SetBulletDir(Direction8::Right);
	}

	// ��
	else if (CharacterAimDir::Up == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ 0.0f, 130.0f };
		NewBullet->SetBulletDir(Direction8::Up);
	}

	// �Ʒ�
	else if (CharacterAimDir::Down == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ 0.0f, 00.0f };
		NewBullet->SetBulletDir(Direction8::Down);
	}

	// ���� ��
	else if (ActorDir::Left == Dir && CharacterAimDir::StraightUp == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 110.0f };
		NewBullet->SetBulletDir(Direction8::LeftUp);
	}

	// ���� �Ʒ�
	else if (ActorDir::Left == Dir && CharacterAimDir::StraightDown == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 20.0f };
		NewBullet->SetBulletDir(Direction8::LeftDown);
	}

	// ������ ��
	else if (ActorDir::Right == Dir && CharacterAimDir::StraightUp == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 110.0f };
		NewBullet->SetBulletDir(Direction8::RightUp);
	}

	// ������ �Ʒ�
	else if (ActorDir::Right == Dir && CharacterAimDir::StraightDown == AimDir)
	{
		CreateSpecialDust();
		NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 20.0f };
		NewBullet->SetBulletDir(Direction8::RightDown);
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