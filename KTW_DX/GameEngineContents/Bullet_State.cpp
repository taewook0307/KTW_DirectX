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

	if (BulletDirection::Right == BulletDir)
	{
		MovePos = float4::RIGHT * Speed * _Delta;
	}

	else if (BulletDirection::Left == BulletDir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
	}

	else if (BulletDirection::Up == BulletDir)
	{
		MovePos = float4::UP * Speed * _Delta;
	}

	else if (BulletDirection::Down == BulletDir)
	{
		MovePos = float4::DOWN * Speed * _Delta;
	}

	Transform.AddLocalPosition(MovePos);



	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	float4 WinLeftPos = { CameraPos.X - WinHalfScale.X, CameraPos.Y + WinHalfScale.Y };
	float4 WinRightPos = { CameraPos.X + WinHalfScale.X, CameraPos.Y - WinHalfScale.Y };

	float4 BulletPos = Transform.GetWorldPosition();

	if (BulletPos.X < WinLeftPos.X
		|| BulletPos.X >= WinRightPos.X
		|| BulletPos.Y > WinLeftPos.Y
		|| BulletPos.Y <= WinRightPos.Y)
	{
		ChangeBulletState(BulletState::Death);
		return;
	}
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