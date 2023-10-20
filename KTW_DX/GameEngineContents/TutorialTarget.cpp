#include "PreCompile.h"
#include "TutorialTarget.h"

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

	TargetCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::UnDamageBoss);
	TargetCollision->Transform.SetLocalScale(TARGETCOLLISIONSCALE);
	TargetCollision->Transform.SetLocalPosition(TARGETRENDERERPOSITION);
}

void TutorialTarget::Update(float _Delta)
{

}