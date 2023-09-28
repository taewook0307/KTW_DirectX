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
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	Renderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	Renderer->CreateAnimation("Start_Effect", "StageStart_Effect", 0.05f, -1, -1, false);
	Renderer->SetEndEvent("Start_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);

	Renderer->ChangeAnimation("Start_Effect");
	Renderer->SetImageScale(WinScale);
}