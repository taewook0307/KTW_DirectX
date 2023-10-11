#include "PreCompile.h"
#include "StageStartUI.h"

StageStartUI::StageStartUI()
{
}

StageStartUI::~StageStartUI()
{
}

void StageStartUI::Start()
{
	EffectRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	EffectRenderer->CreateAnimation("Start_Effect", "StageStart_Effect", 0.05f, -1, -1, false);
	EffectRenderer->SetEndEvent("Start_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			EffectRenderer = nullptr;
			Death();
		}
	);

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	EffectRenderer->SetImageScale(WinScale);

	EffectRenderer->ChangeAnimation("Start_Effect");
}