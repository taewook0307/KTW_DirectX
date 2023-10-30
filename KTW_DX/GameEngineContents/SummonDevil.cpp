#include "PreCompile.h"
#include "SummonDevil.h"

SummonDevil::SummonDevil()
{
}

SummonDevil::~SummonDevil()
{
}

void SummonDevil::Start()
{
	SummonDevilRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperMap1);
	SummonDevilRenderer->AutoSpriteSizeOn();
	SummonDevilRenderer->SetPivotType(PivotType::RightBottom);

	SummonDevilRenderer->CreateAnimation("SummonDevil_Intro", "SummonDevil_Intro");
	SummonDevilRenderer->SetEndEvent("SummonDevil_Intro",
		[=](GameEngineSpriteRenderer* _Parent)
		{
			SummonDevilRenderer->ChangeAnimation("SummonDevil_Jump");
		}
	);
	SummonDevilRenderer->CreateAnimation("SummonDevil_Jump", "SummonDevil_Jump", 0.1f, -1, -1, false);
	SummonDevilRenderer->SetEndEvent("SummonDevil_Jump",
		[=](GameEngineSpriteRenderer* _Parent)
		{
			SummonDevilRenderer->ChangeAnimation("SummonDevil_Move");
		}
	);
	SummonDevilRenderer->CreateAnimation("SummonDevil_Move", "SummonDevil_Move", 0.1f);

	SummonDevilRenderer->ChangeAnimation("SummonDevil_Intro");

	GameEngineInput::AddInputObject(this);
}

void SummonDevil::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1', this))
	{
		SummonDevilRenderer->ChangeAnimation("SummonDevil_Intro");
	}

	if (true == GameEngineInput::IsDown('2', this))
	{
		SummonDevilRenderer->ChangeAnimation("SummonDevil_Jump");
	}

	if (true == GameEngineInput::IsDown('3', this))
	{
		SummonDevilRenderer->ChangeAnimation("SummonDevil_Move");
	}
}