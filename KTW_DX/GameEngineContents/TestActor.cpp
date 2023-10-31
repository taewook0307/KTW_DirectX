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
	TestRenderer->CreateAnimation("Serpent_Head", "Serpent_Head", 0.1f, 0, 23, true);
	TestRenderer->SetPivotType(PivotType::RightBottom);
	TestRenderer->AutoSpriteSizeOn();

	TestRenderer->ChangeAnimation("Serpent_Head");
}

void TestActor::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P', this))
	{
		TestRenderer->ChangeAnimation("Serpent_Head", true);
	}
}