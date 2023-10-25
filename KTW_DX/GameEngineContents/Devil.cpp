#include "PreCompile.h"
#include "Devil.h"

Devil::Devil()
{
}

Devil::~Devil()
{
}

void Devil::Start()
{
	DevilRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	DevilRenderer->AutoSpriteSizeOn();
	DevilRenderer->SetPivotType(PivotType::Bottom);
	DevilRenderer->CreateAnimation("Devil_Intro", "Devil_Intro", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;

		Para.Start = [=](GameEngineState* _Parent)
			{
				DevilRenderer->ChangeAnimation("Devil_Intro");
			};

		DevilState.CreateState(EDEVILSTATE::Intro, Para);
	}

	DevilState.ChangeState(EDEVILSTATE::Intro);
}

void Devil::Update(float _Delta)
{
	DevilState.Update(_Delta);
}