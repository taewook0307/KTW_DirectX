#include "PreCompile.h"
#include "WorldMapFlag.h"

WorldMapFlag::WorldMapFlag()
{
}

WorldMapFlag::~WorldMapFlag()
{
}

void WorldMapFlag::Start()
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
					FlagState.ChangeState(EWorldMapFlag::Rise);
					return;
				}
			};
		FlagState.CreateState(EWorldMapFlag::Appear, Para);
	}

	// Rise State
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _State)
			{
				GameEngineSound::SoundPlay("flag_raise.wav");
				FlagRenderer->ChangeAnimation("Flag_Rise");
			};
		Para.Stay =
			[=](float _DeltaTime, GameEngineState* _State)
			{
				if (true == FlagRenderer->IsCurAnimationEnd())
				{
					FlagState.ChangeState(EWorldMapFlag::Stay);
					return;
				}
			};
		FlagState.CreateState(EWorldMapFlag::Rise, Para);
	}

	// Stay State
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _State) { FlagRenderer->ChangeAnimation("Flag_Stay"); };
		FlagState.CreateState(EWorldMapFlag::Stay, Para);
	}

	FlagState.ChangeState(EWorldMapFlag::Appear);
}

void WorldMapFlag::Update(float _Delta)
{
	FlagState.Update(_Delta);
}