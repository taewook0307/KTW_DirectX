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
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::BackGround));
}

void BackGround::Update(float _Delta)
{

}

void BackGround::BackGroundInit(std::string_view _FileName, int _Order /*= 0*/)
{
	MainSpriteRenderer->SetSprite(_FileName, _Order);
	MainSpriteRenderer->Transform.SetLocalScale(GameEngineCore::MainWindow.GetScale());
}

void BackGround::AnimationInit(std::string_view _AnimationName, std::string_view _FileName, float _Inter /*= 0.1f*/, bool _Loop /*= true*/, bool _SizeFixWindow /*= true*/, unsigned int _Start /*= -1*/, unsigned int _End /*= -1*/)
{
	MainSpriteRenderer->CreateAnimation(_AnimationName, _FileName, _Inter, _Start, _End, _Loop);
	MainSpriteRenderer->ChangeAnimation(_AnimationName);

	if (true == _SizeFixWindow)
	{
		MainSpriteRenderer->Transform.SetLocalScale(GameEngineCore::MainWindow.GetScale());
	}
	else
	{
		MainSpriteRenderer->AutoSpriteSizeOn();
	}
}