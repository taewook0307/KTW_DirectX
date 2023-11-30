#include "PreCompile.h"
#include "TutorialTarget.h"

#include "TargetExplosionEffect.h"

TutorialTarget::TutorialTarget()
{
}

TutorialTarget::~TutorialTarget()
{
}

void TutorialTarget::Start()
{
	MainRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
	MainRenderer->SetSprite("tutorial_pyramid_topper.Png");
	MainRenderer->AutoSpriteSizeOn();
	MainRenderer->SetAutoScaleRatio(0.8f);

	MainCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::Obstacle);
	std::shared_ptr<GameEngineSprite> MainRendererSprite = GameEngineSprite::Find("tutorial_pyramid_topper.Png");
	float4 CollisionScale = MainRendererSprite->GetSpriteData(0).GetScale();
	MainCollision->Transform.SetLocalScale(CollisionScale * 0.8f);
	MainCollision->SetCollisionType(ColType::AABBBOX2D);

	TargetRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperMap);
	TargetRenderer->CreateAnimation("Target_Idle", "Target");
	TargetRenderer->AutoSpriteSizeOn();
	TargetRenderer->SetAutoScaleRatio(0.8f);
	TargetRenderer->Transform.SetLocalPosition(TARGETRENDERERPOSITION);
	TargetRenderer->ChangeAnimation("Target_Idle");

	TargetCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::TutorialTarget);
	TargetCollision->Transform.SetLocalScale(TARGETCOLLISIONSCALE);
	TargetCollision->Transform.SetLocalPosition(TARGETRENDERERPOSITION);


}

void TutorialTarget::Update(float _Delta)
{
	if (HitCount > 10)
	{
		CreateExplosionEffect();
		Death();
	}
}

void TutorialTarget::CreateExplosionEffect()
{
	GameEngineSound::SoundPlay("sfx_clown_bulb_explosion_01.wav");

	std::shared_ptr<TargetExplosionEffect> Effect = GetLevel()->CreateActor<TargetExplosionEffect>(EUPDATEORDER::Effect);

	float4 Pos = Transform.GetWorldPosition();

	Effect->Transform.SetLocalPosition(Pos);
}