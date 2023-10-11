#include "PreCompile.h"
#include "StageFailUI.h"

StageFailUI::StageFailUI()
{
}

StageFailUI::~StageFailUI()
{
}

void StageFailUI::Start()
{
	EffectRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	EffectRenderer->CreateAnimation("Fail_Effect", "StageFail_Effect", 0.1f, -1, -1, false);
	EffectRenderer->SetEndEvent("Fail_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			EffectRenderer = nullptr;
			Death();
		}
	);

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	EffectRenderer->SetImageScale(WinScale);

	EffectRenderer->ChangeAnimation("Fail_Effect");
}