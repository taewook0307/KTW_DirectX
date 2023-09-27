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
	Renderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	Renderer->CreateAnimation("Fail_Effect", "StageFail_Effect", 0.1f, -1, -1, false);
	Renderer->SetEndEvent("Fail_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer = nullptr;
			Death();
		}
	);

	Renderer->ChangeAnimation("Fail_Effect");
	Renderer->Transform.SetLocalScale({ 1280.0f, 720.0f });
}