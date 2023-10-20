#include "PreCompile.h"
#include "Bullet.h"

void Bullet::SpawnStart()
{
	ChangeBulletAnimation("Spawn");
}

void Bullet::SpawnUpdate(float _Delta)
{
	if (true == BulletRenderer->IsCurAnimationEnd())
	{
		ChangeBulletState(EBULLETSTATE::Move);
		return;
	}
}

void Bullet::MoveStart()
{
	ChangeBulletAnimation("Move");
	BulletCollision->On();
}

void Bullet::MoveUpdate(float _Delta)
{
	float Speed = 1000.0f;
	float4 MovePos = float4::RIGHT * Speed * _Delta;

	if (EDIRECTION8::Right == BulletDir)
	{
		MovePos = float4::RIGHT * Speed * _Delta;
	}

	else if (EDIRECTION8::Left == BulletDir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
	}

	else if (EDIRECTION8::Up == BulletDir)
	{
		MovePos = float4::UP * Speed * _Delta;
	}

	else if (EDIRECTION8::Down == BulletDir)
	{
		MovePos = float4::DOWN * Speed * _Delta;
	}

	else if (EDIRECTION8::LeftUp == BulletDir)
	{
		MovePos = (float4::UP + float4::LEFT) * Speed * _Delta;
	}

	else if (EDIRECTION8::LeftDown == BulletDir)
	{
		MovePos = (float4::DOWN + float4::LEFT) * Speed * _Delta;
	}

	else if (EDIRECTION8::RightUp == BulletDir)
	{
		MovePos = (float4::UP + float4::RIGHT) * Speed * _Delta;
	}

	else if (EDIRECTION8::RightDown == BulletDir)
	{
		MovePos = (float4::DOWN + float4::RIGHT) * Speed * _Delta;
	}

	Transform.AddLocalPosition(MovePos);

	PosCheck();
	ColCheck();
}

void Bullet::DeathStart()
{
	ChangeBulletAnimation("Death");
}

void Bullet::DeathUpdate(float _Delta)
{
	if (true == BulletRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}