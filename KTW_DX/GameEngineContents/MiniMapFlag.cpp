#include "PreCompile.h"
#include "MiniMapFlag.h"

MiniMapFlag::MiniMapFlag()
{
}

MiniMapFlag::~MiniMapFlag()
{
}

void MiniMapFlag::Start()
{
	FlagRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperMap);
	FlagRenderer->CreateAnimation("Flag_Appear", "Flag_Appear", 0.1f, -1, -1, false);
	FlagRenderer->CreateAnimation("Flag_Rise", "Flag_Rise", 0.1f, -1, -1, false);
	FlagRenderer->CreateAnimation("Flag_Stay", "Flag_Stay", 0.1f, -1, -1, true);
	FlagRenderer->AutoSpriteSizeOn();
	FlagRenderer->SetPivotType(PivotType::Bottom);

	// Appear State
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _State) { FlagRenderer->ChangeAnimation("Flag_Appear"); };
		Para.Stay =
			[=](float _DeltaTime, GameEngineState* _State)
			{
				if (true == FlagRenderer->IsCurAnimationEnd())
				{
					FlagState.ChangeState(EMINIMAPFLAG::Rise);
					return;
				}
			};
		FlagState.CreateState(EMINIMAPFLAG::Appear, Para);
	}

	// Rise State
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _State) { FlagRenderer->ChangeAnimation("Flag_Rise"); };
		Para.Stay =
			[=](float _DeltaTime, GameEngineState* _State)
			{
				if (true == FlagRenderer->IsCurAnimationEnd())
				{
					FlagState.ChangeState(EMINIMAPFLAG::Stay);
					return;
				}
			};
		FlagState.CreateState(EMINIMAPFLAG::Rise, Para);
	}

	// Stay State
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _State) { FlagRenderer->ChangeAnimation("Flag_Stay"); };
		FlagState.CreateState(EMINIMAPFLAG::Stay, Para);
	}

	FlagState.ChangeState(EMINIMAPFLAG::Appear);
}

void MiniMapFlag::Update(float _Delta)
{
	FlagState.Update(_Delta);
}