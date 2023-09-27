#include "PreCompile.h"
#include "PirateBullet.h"

void PirateBullet::CameraOutCheck()
{
	float4 BulletPos = Transform.GetWorldPosition();
	
	if (0 > BulletPos.X
		|| -720.0f > BulletPos.Y)
	{
		ChangeState(EPIRATEBULLETSTATE::Death);
		return;
	}
}

void PirateBullet::MoveStart()
{
	ChangeAnimation("Move");
}

void PirateBullet::MoveUpdate(float _Delta)
{
	if (false == DirVectorSet)
	{
		DirVector = PlayerPos - Transform.GetWorldPosition();
		DirVectorSet = true;
	}

	float4 MovePos = DirVector.NormalizeReturn() * _Delta * Speed;
	Transform.AddLocalPosition(MovePos);

	CameraOutCheck();
}

void PirateBullet::DeathStart()
{
	ChangeAnimation("Death");
}

void PirateBullet::DeathUpdate(float _Delta)
{
	BulletCollision->Off();
}