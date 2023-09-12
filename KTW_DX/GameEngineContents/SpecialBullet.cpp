#include "PreCompile.h"
#include "SpecialBullet.h"

SpecialBullet::SpecialBullet()
{
}

SpecialBullet::~SpecialBullet()
{
}

void SpecialBullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Bullet);
	BulletRenderer->CreateAnimation("EXBullet_Spawn", "EXBulletSpawn", 0.02f);
	BulletRenderer->CreateAnimation("EXBullet_Move", "EXBulletMove", 0.02f);
	BulletRenderer->CreateAnimation("EXBullet_Death", "EXBulletDeath", 0.02f);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetAutoScaleRatio(BULLETRATIO);

	ChangeBulletState(BulletState::Spawn);
}

void SpecialBullet::ChangeBulletAnimation(std::string_view _State)
{
	std::string AnimationName = "EXBullet_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}