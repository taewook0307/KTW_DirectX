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
	TestRenderer->CreateAnimation("Devil_Serpent", "Devil_Serpent", 0.1f, -1, -1, false);
	TestRenderer->SetPivotType(PivotType::Bottom);
	TestRenderer->AutoSpriteSizeOn();

	TestRenderer->ChangeAnimation("Devil_Serpent");
}

void TestActor::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P', this))
	{
		TestRenderer->ChangeAnimation("Devil_Serpent", true);
	}
}