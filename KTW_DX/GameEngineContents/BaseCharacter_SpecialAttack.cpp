#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"
#include "SpecialBullet.h"


void BaseCharacter::SpecialShootState()
{
	std::shared_ptr<SpecialBullet> NewBullet = GetLevel()->CreateActor<SpecialBullet>(UpdateOrder::Bullet);
	float4 NewBulletPos = float4::ZERO;

	// ����
	if (CharacterDir::Left == Dir && CharacterAimDir::Straight == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 60.0f };
		NewBullet->SetBulletDir(BulletDirection::Left);
	}

	// ������
	else if (CharacterDir::Right == Dir && CharacterAimDir::Straight == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 60.0f };
		NewBullet->SetBulletDir(BulletDirection::Right);
	}

	// ��(����)
	else if (CharacterDir::Left == Dir && CharacterAimDir::Up == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ -30.0f, 130.0f };
		NewBullet->SetBulletDir(BulletDirection::Up);
	}

	// �Ʒ�(����)
	else if (CharacterDir::Left == Dir && CharacterAimDir::Down == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ -20.0f, 00.0f };
		NewBullet->SetBulletDir(BulletDirection::Down);
	}

	// ��(������)
	else if (CharacterDir::Right == Dir && CharacterAimDir::Up == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ 30.0f, 130.0f };
		NewBullet->SetBulletDir(BulletDirection::Up);
	}

	// �Ʒ�(������)
	else if (CharacterDir::Right == Dir && CharacterAimDir::Down == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ 20.0f, 00.0f };
		NewBullet->SetBulletDir(BulletDirection::Down);
	}

	// ���� ��
	else if (CharacterDir::Left == Dir && CharacterAimDir::StraightUp == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 110.0f };
		NewBullet->SetBulletDir(BulletDirection::LeftUp);
	}

	// ���� �Ʒ�
	else if (CharacterDir::Left == Dir && CharacterAimDir::StraightDown == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 20.0f };
		NewBullet->SetBulletDir(BulletDirection::LeftDown);
	}

	// ������ ��
	else if (CharacterDir::Right == Dir && CharacterAimDir::StraightUp == AimDir)
	{
		NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 110.0f };
		NewBullet->SetBulletDir(BulletDirection::RightUp);
	}

	// ������ �Ʒ�
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
	SpecialShootState();

	if (true == PlayerRenderer->IsCurAnimationEnd())
	{
		ChangeState(CharacterState::Idle);
		return;
	}
}