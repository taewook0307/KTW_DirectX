#include "PreCompile.h"
#include "ClearEffect.h"

ClearEffect::ClearEffect()
{
}

ClearEffect::~ClearEffect()
{
}

void ClearEffect::Start()
{
	ClearRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	ClearRenderer->AutoSpriteSizeOn();
	ClearRenderer->CreateAnimation("Clear_Effect", "StageClear_Effect", 0.1f, -1, -1, false);
	ClearRenderer->SetEndEvent("Clear_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ClearRenderer = nullptr;
			Death();
		}
	);

	ClearRenderer->ChangeAnimation("Clear_Effect");
}