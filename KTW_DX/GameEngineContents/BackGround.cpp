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

void BackGround::AnimationInit(std::string_view _AnimationName, std::string_view _FileName, float _Inter /*= 0.1f*/, unsigned int _Start /*= -1*/, unsigned int _End /*= -1*/, bool _Loop /*= true*/)
{
	MainSpriteRenderer->CreateAnimation(_AnimationName, _FileName, _Inter, _Start, _End, _Loop);
	MainSpriteRenderer->ChangeAnimation(_AnimationName);
	MainSpriteRenderer->Transform.SetLocalScale(GameEngineCore::MainWindow.GetScale());
}