#include "PreCompile.h"
#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::BackGroundInit(std::string_view _FileName, int _Order /*= 0*/)
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
	MainSpriteRenderer->SetSprite(_FileName, _Order);
	MainSpriteRenderer->Transform.SetLocalScale(GameEngineCore::MainWindow.GetScale());
}

void BackGround::Update(float _Delta)
{
	
}