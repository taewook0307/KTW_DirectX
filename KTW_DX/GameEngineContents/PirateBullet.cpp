#include "PreCompile.h"
#include "PirateBullet.h"

#include "BaseCharacter.h"

PirateBullet::PirateBullet()
{
}

PirateBullet::~PirateBullet()
{
}

void PirateBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	BulletRenderer->CreateAnimation("Pirate_Bullet_Yellow_Move", "Pirate_Bullet_Yellow_Move");
	BulletRenderer->CreateAnimation("Pirate_Bullet_Yellow_Death", "Pirate_Bullet_Yellow_Death");
	BulletRenderer->SetEndEvent("Pirate_Bullet_Yellow_Death",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetPivotType(PivotType::Left);

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterAttack);
	BulletCollision->Transform.SetLocalScale({ 10.0f, 10.0f });

	PlayerPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	ChangeState(EPIRATEBULLETSTATE::Move);
}

void PirateBullet::Update(float _Delta)
{
	StateUpdate(_Delta);

	BulletCollision->Collision(ECOLLISIONORDER::Player,
		[=](std::vector<std::shared_ptr<GameEngineCollision>>& _ColVector)
		{
			ChangeState(EPIRATEBULLETSTATE::Death);
			return;
		}
	);
}

void PirateBullet::ChangeState(EPIRATEBULLETSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case EPIRATEBULLETSTATE::Move:
			MoveStart();
			break;
		case EPIRATEBULLETSTATE::Death:
			DeathStart();
			break;
		default:
			break;
		}

		CurState = _State;
	}
}

void PirateBullet::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case EPIRATEBULLETSTATE::Move:
		return MoveUpdate(_Delta);
	case EPIRATEBULLETSTATE::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void PirateBullet::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Pirate_Bullet_Yellow_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}