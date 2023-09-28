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
	Renderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	Renderer->CreateAnimation("Clear_Effect", "StageClear_Effect", 0.1f, -1, -1, false);
	Renderer->SetEndEvent("Clear_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	Renderer->SetImageScale(WinScale);

	Renderer->ChangeAnimation("Clear_Effect");
}