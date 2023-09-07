#include "PreCompile.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Bullet);
	BulletRenderer->CreateAnimation("Bullet_Spawn", "BulletSpawn", 0.02f);
	BulletRenderer->CreateAnimation("Bullet_Move", "BulletMove", 0.02f);
	BulletRenderer->CreateAnimation("Bullet_Death", "BulletDeath", 0.02f);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetAutoScaleRatio(0.3f);

	ChangeBulletState(BulletState::Spawn);
}

void Bullet::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Bullet::ChangeBulletState(BulletState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case BulletState::Spawn:
			SpawnStart();
			break;
		case BulletState::Move:
			MoveStart();
			break;
		case BulletState::Death:
			DeathStart();
			break;
		default:
			break;
		}

		CurState = _State;
	}
}

void Bullet::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case BulletState::Spawn:
		return SpawnUpdate(_Delta);
	case BulletState::Move:
		return MoveUpdate(_Delta);
	case BulletState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void Bullet::ChangeBulletAnimation(std::string_view _State)
{
	std::string AnimationName = "Bullet_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}