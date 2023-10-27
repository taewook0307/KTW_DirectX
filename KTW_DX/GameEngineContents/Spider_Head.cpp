#include "PreCompile.h"
#include "Spider_Head.h"

Spider_Head::Spider_Head()
{
}

Spider_Head::~Spider_Head()
{
}

void Spider_Head::Start()
{
	SpiderRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	SpiderRenderer->AutoSpriteSizeOn();
	SpiderRenderer->SetPivotType(PivotType::Bottom);
	SpiderRenderer->CreateAnimation("Spider_Idle", "Spider_Head");

	CreateStateParameter Para;
	Para.Start = [=](GameEngineState* _Parent)
		{
			SpiderRenderer->ChangeAnimation("Spider_Idle");
		};

	SpiderState.CreateState(0, Para);

	SpiderState.ChangeState(0);
}

void Spider_Head::Update(float _Delta)
{
	SpiderState.Update(_Delta);
}