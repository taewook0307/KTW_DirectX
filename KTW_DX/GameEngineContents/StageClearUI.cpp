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
	Renderer->AutoSpriteSizeOn();
	Renderer->CreateAnimation("Clear_Effect", "StageClear_Effect", 0.1f, -1, -1, false);
	Renderer->SetEndEvent("Clear_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);

	Renderer->ChangeAnimation("Clear_Effect");
}