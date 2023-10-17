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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	Renderer->CreateAnimation("Pirate_Bullet_Yellow_Move", "Pirate_Bullet_Yellow_Move");
	Renderer->CreateAnimation("Pirate_Bullet_Yellow_Death", "Pirate_Bullet_Yellow_Death");
	Renderer->SetEndEvent("Pirate_Bullet_Yellow_Death",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);
	Renderer->SetPivotType(PivotType::Left);
	Renderer->AutoSpriteSizeOn();

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	BulletCollision->Transform.SetLocalScale(PIRATEBULLETCOLLISIONSCALE);
	BulletCollision->Transform.SetLocalPosition(PIRATEBULLETCOLLISIONPOSITION);

	float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	PlayerPos = { CharacterPos.X, CharacterPos.Y + ADJUSTVALUE };
	ChangeState(EPIRATEBULLETSTATE::Move);
}

void PirateBullet::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void PirateBullet::ChangeState(EPIRATEBULLETSTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
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

		CurState = _CurState;
	}
}

void PirateBullet::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case EPIRATEBULLETSTATE::Move:
		return MoveUpdate(_Delta);
	default:
		break;
	}
}

void PirateBullet::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Pirate_Bullet_Yellow_";

	AnimationName += _State;

	State = _State;

	Renderer->ChangeAnimation(AnimationName);
}

void PirateBullet::HitCheck()
{
	if (true == BulletCollision->Collision(ECOLLISIONORDER::Player) && EPIRATEBULLETSTATE::Death != CurState)
	{
		ChangeState(EPIRATEBULLETSTATE::Death);
		return;
	}
}