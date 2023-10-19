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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PrevBoss5);
	Renderer->CreateAnimation("Pirate_Bullet_Pink_Move", "Pirate_Bullet_Pink_Move");
	Renderer->CreateAnimation("Pirate_Bullet_Pink_Death", "Pirate_Bullet_Pink_Death");
	Renderer->SetEndEvent("Pirate_Bullet_Pink_Death",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Left);

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

	Renderer->ChangeAnimation(AnimationName);
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