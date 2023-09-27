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
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	ClearRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	//ClearRenderer->Transform.SetLocalScale(WinScale);
	ClearRenderer->AutoSpriteSizeOn();
	ClearRenderer->CreateAnimation("Clear_Effect", "Clear_Effect", 0.1f, -1, -1, false);
	ClearRenderer->SetEndEvent("Clear_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ClearRenderer = nullptr;
			Death();
		}
	);

	ClearRenderer->ChangeAnimation("Clear_Effect");
}