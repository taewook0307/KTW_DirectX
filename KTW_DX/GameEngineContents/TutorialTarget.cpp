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
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
	BodyRenderer->SetSprite("tutorial_pyramid_topper.Png");
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(0.8f);

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
	OutputDebugStringA(std::to_string(HitCount).c_str());
	OutputDebugStringA("\n");

	if (HitCount > 10)
	{
		CreateExplosionEffect();
		Death();
	}
}

void TutorialTarget::CreateExplosionEffect()
{
	std::shared_ptr<TargetExplosionEffect> Effect = GetLevel()->CreateActor<TargetExplosionEffect>(EUPDATEORDER::Effect);

	float4 Pos = Transform.GetWorldPosition();

	Effect->Transform.SetLocalPosition(Pos);
}