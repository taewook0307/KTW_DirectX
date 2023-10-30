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
	TestRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	TestRenderer->CreateAnimation("Devil_Attack", "Devil_Attack", 0.1f, -1, -1, false);
	TestRenderer->AutoSpriteSizeOn();
	TestRenderer->SetPivotType(PivotType::Bottom);
	TestRenderer->SetEndEvent("Devil_Attack", [=](GameEngineSpriteRenderer* _Parent)
		{
			TestRenderer->Off();
			HeadRenderer->On();
			HeadRenderer->ChangeAnimation("Devil_Attack_Head");
			BodyRenderer->On();
			BodyRenderer->ChangeAnimation("Devil_Attack_Body");
			TridentRenderer->On();
			TridentRenderer->ChangeAnimation("Devil_Attack_Trident");
		}
	);

	TestRenderer->CreateAnimation("Devil_Attack_End", "Devil_Attack", 0.1f, 7, 0, false);

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	BodyRenderer->CreateAnimation("Devil_Attack_Body", "Devil_Attack_Body", 0.1f);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->Off();

	HeadRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	HeadRenderer->CreateAnimation("Devil_Attack_Head", "Devil_Attack_Head", 0.1f);
	HeadRenderer->AutoSpriteSizeOn();
	HeadRenderer->SetPivotType(PivotType::Bottom);
	HeadRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	HeadRenderer->Off();

	TridentRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	TridentRenderer->CreateAnimation("Devil_Attack_Trident", "Devil_Attack_Trident", 0.1f, -1, -1, false);
	/*TridentRenderer->SetFrameEvent("Devil_Attack_Trident", 33, [=](GameEngineSpriteRenderer* _Parent)
		{
			HeadRenderer->Off();
			BodyRenderer->Off();
			TestRenderer->On();
			TestRenderer->ChangeAnimation("Devil_Attack_End");
		}
	);*/
	TridentRenderer->SetEndEvent("Devil_Attack_Trident", [=](GameEngineSpriteRenderer* _Parent)
		{
			TridentRenderer->Off();
			HeadRenderer->Off();
			BodyRenderer->Off();
			TestRenderer->On();
			TestRenderer->ChangeAnimation("Devil_Attack_End");
		}
	);
	TridentRenderer->AutoSpriteSizeOn();
	TridentRenderer->Transform.SetLocalPosition({ 20.0f, 350.0f });
	TridentRenderer->Off();

	TestRenderer->ChangeAnimation("Devil_Attack");
}