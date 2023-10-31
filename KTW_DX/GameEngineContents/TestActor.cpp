#include "PreCompile.h"
#include "TestActor.h"

TestActor::TestActor()
{
}

TestActor::~TestActor()
{
}

void TestActor::Start()
{
	GameEngineInput::AddInputObject(this);

	TestRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	TestRenderer->CreateAnimation("Intro_Eye", "Intro_Eye", 0.1f, -1, -1, false);
	TestRenderer->SetPivotType(PivotType::Right);
	TestRenderer->AutoSpriteSizeOn();

	TestRenderer->ChangeAnimation("Intro_Eye");
}

void TestActor::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P', this))
	{
		TestRenderer->ChangeAnimation("Intro_Eye", true);
	}
}