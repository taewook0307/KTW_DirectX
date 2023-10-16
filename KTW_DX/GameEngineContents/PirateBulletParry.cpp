#include "PreCompile.h"
#include "PirateBulletParry.h"

#include "BaseCharacter.h"

PirateBulletParry::PirateBulletParry()
{
}

PirateBulletParry::~PirateBulletParry()
{
}

void PirateBulletParry::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Bullet);
	BulletRenderer->CreateAnimation("Pirate_Bullet_Pink_Move", "Pirate_Bullet_Pink_Move");
	BulletRenderer->CreateAnimation("Pirate_Bullet_Pink_Death", "Pirate_Bullet_Pink_Death");
	BulletRenderer->SetEndEvent("Pirate_Bullet_Pink_Death",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BulletRenderer = nullptr;
			Death();
		}
	);
	BulletRenderer->SetPivotType(PivotType::Left);
	BulletRenderer->AutoSpriteSizeOn();

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	BulletCollision->Transform.SetLocalScale(PIRATEBULLETCOLLISIONSCALE);
	BulletCollision->Transform.SetLocalPosition(PIRATEBULLETCOLLISIONPOSITION);

	ParryCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::ParryObject);
	ParryCollision->Transform.SetLocalScale(PIRATEBULLETCOLLISIONSCALE);
	ParryCollision->Transform.SetLocalPosition(PIRATEBULLETCOLLISIONPOSITION);

	float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	PlayerPos = { CharacterPos.X, CharacterPos.Y + ADJUSTVALUE };
	ChangeState(EPIRATEBULLETSTATE::Move);
}

void PirateBulletParry::Update(float _Delta)
{
	PirateBullet::Update(_Delta);
}

void PirateBulletParry::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Pirate_Bullet_Pink_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}

void PirateBulletParry::HitCheck()
{
	if (false == ParryActivation)
	{
		BulletCollision->Off();
		ChangeState(EPIRATEBULLETSTATE::Death);
		return;
	}
	else
	{
		if (true == BulletCollision->Collision(ECOLLISIONORDER::Player) && EPIRATEBULLETSTATE::Death != CurState)
		{
			ChangeState(EPIRATEBULLETSTATE::Death);
			return;
		}
	}
}