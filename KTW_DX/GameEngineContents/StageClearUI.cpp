#include "PreCompile.h"
#include "StageClearUI.h"

StageClearUI::StageClearUI()
{
}

StageClearUI::~StageClearUI()
{
}

void StageClearUI::Start()
{
	EffectRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	EffectRenderer->CreateAnimation("Clear_Effect", "StageClear_Effect", 0.1f, -1, -1, false);
	
	EffectRenderer->SetStartEvent("Clear_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_level_knockout_bell.wav");
			GameEngineSound::SoundPlay("sfx_level_announcer_knockout_0004.wav");
		}
	);
	EffectRenderer->SetEndEvent("Clear_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	EffectRenderer->SetImageScale(WinScale);

	EffectRenderer->ChangeAnimation("Clear_Effect");
}