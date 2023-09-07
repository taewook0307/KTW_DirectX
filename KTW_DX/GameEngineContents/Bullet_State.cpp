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
		ChangeBulletState(BulletState::Move);
		return;
	}
}

void Bullet::MoveStart()
{
	ChangeBulletAnimation("Move");
}

void Bullet::MoveUpdate(float _Delta)
{
	float Speed = 700.0f;
	float4 MovePos = float4::RIGHT * Speed * _Delta;

	Transform.AddLocalPosition(MovePos);

	/*float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	float4 WindowOutCheckPos = WinScale;

	float4 BulletPos = Transform.GetWorldPosition();

	if (BulletPos.X < 0.0f
		|| BulletPos.X >= WindowOutCheckPos.X
		|| BulletPos.Y > 0.0f
		|| BulletPos.Y <= WindowOutCheckPos.Y)
	{
		ChangeBulletState(BulletState::Death);
		return;
	}*/
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