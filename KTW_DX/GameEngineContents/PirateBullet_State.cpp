#include "PreCompile.h"
#include "PirateBullet.h"

void PirateBullet::CameraOutCheck()
{
	float4 BulletPos = Transform.GetWorldPosition();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	
	if (-200.0f > BulletPos.X
		|| WinScale.X + 200.0f < BulletPos.X
		|| 200.0f < BulletPos.Y
		|| -WinScale.Y - 200.0f > BulletPos.Y)
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
	BulletCollision->Off();
	ChangeAnimation("Death");
}