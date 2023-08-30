#include "PreCompile.h"
#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
}

void BackGround::Update(float _Delta)
{
	
}

void BackGround::BackGroundInit(std::string_view _FileName, int _Order /*= 0*/)
{
	MainSpriteRenderer->SetSprite(_FileName, _Order);
	MainSpriteRenderer->Transform.SetLocalScale(GameEngineCore::MainWindow.GetScale());
}