#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"
#include "SpecialBullet.h"


void BaseCharacter::SpecialShootState()
{
	std::shared_ptr<SpecialBullet> NewBullet = GetLevel()->CreateActor<SpecialBullet>(EUPDATEORDER::Bullet);
	float4 NewBulletPos = float4::ZERO;

	// 왼쪽
	if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::Straight == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::Left);
		NewBulletPos = Transform.GetWorldPosition() + float4{ -80.0f, 40.0f };
		NewBullet->SetBulletDir(EDIRECTION8::Left);
	}

	// 오른쪽
	else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::Straight == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::Right);
		NewBulletPos = Transform.GetWorldPosition() + float4{ 80.0f, 40.0f };
		NewBullet->SetBulletDir(EDIRECTION8::Right);
	}

	// 위
	else if (ECHARACTERAIMDIR::Up == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::Up);
		NewBulletPos = Transform.GetWorldPosition() + float4{ 0.0f, 130.0f };
		NewBullet->SetBulletDir(EDIRECTION8::Up);
	}

	// 아래
	else if (ECHARACTERAIMDIR::Down == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::Down);
		NewBulletPos = Transform.GetWorldPosition() + float4{ 0.0f, 00.0f };
		NewBullet->SetBulletDir(EDIRECTION8::Down);
	}

	// 왼쪽 위
	else if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::StraightUp == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::LeftUp);
		NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 110.0f };
		NewBullet->SetBulletDir(EDIRECTION8::LeftUp);
	}

	// 왼쪽 아래
	else if (EACTORDIR::Left == Dir && ECHARACTERAIMDIR::StraightDown == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::LeftDown);
		NewBulletPos = Transform.GetWorldPosition() + float4{ -50.0f, 20.0f };
		NewBullet->SetBulletDir(EDIRECTION8::LeftDown);
	}

	// 오른쪽 위
	else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::StraightUp == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::RightUp);
		NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 110.0f };
		NewBullet->SetBulletDir(EDIRECTION8::RightUp);
	}

	// 오른쪽 아래
	else if (EACTORDIR::Right == Dir && ECHARACTERAIMDIR::StraightDown == AimDir)
	{
		CreateSpecialDust(EDIRECTION8::RightDown);
		NewBulletPos = Transform.GetWorldPosition() + float4{ 50.0f, 20.0f };
		NewBullet->SetBulletDir(EDIRECTION8::RightDown);
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
			ChangeState(ECHARACTERSTATE::Fall);
			return;
		}
		else
		{
			ChangeState(ECHARACTERSTATE::Idle);
			return;
		}
	}

	if (true == Cheat && true == PlayerRenderer->IsCurAnimationEnd() && true == GameEngineInput::IsFree('V', this))
	{
		GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

		if (CheckColor != FLOORCOLOR)
		{
			ChangeState(ECHARACTERSTATE::Fall);
			return;
		}
		else
		{
			ChangeState(ECHARACTERSTATE::Idle);
			return;
		}
	}
}