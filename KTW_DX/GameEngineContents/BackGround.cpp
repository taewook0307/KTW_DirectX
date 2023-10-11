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
	BackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackGround);
}

void BackGround::Update(float _Delta)
{

}

void BackGround::BackGroundInit(std::string_view _FileName, int _Order /*= 0*/)
{
	BackGroundRenderer->SetSprite(_FileName, _Order);
	BackGroundRenderer->SetImageScale(GameEngineCore::MainWindow.GetScale());
}

void BackGround::AnimationInit(std::string_view _AnimationName, std::string_view _FileName, float _Inter /*= 0.1f*/, bool _Loop /*= true*/, bool _SizeFixWindow /*= true*/, unsigned int _Start /*= -1*/, unsigned int _End /*= -1*/)
{
	BackGroundRenderer->CreateAnimation(_AnimationName, _FileName, _Inter, _Start, _End, _Loop);
	BackGroundRenderer->ChangeAnimation(_AnimationName);

	if (true == _SizeFixWindow)
	{
		BackGroundRenderer->SetImageScale(GameEngineCore::MainWindow.GetScale());
	}
	else
	{
		BackGroundRenderer->AutoSpriteSizeOn();
	}
}

bool BackGround::AnimationEndCheck()
{
	return BackGroundRenderer->IsCurAnimationEnd();
}

void BackGround::SetBackGroundRendererPivotType(PivotType _Pivot)
{
	BackGroundRenderer->SetPivotType(_Pivot);
}

void BackGround::BackGroundDeath()
{
	BackGroundRenderer = nullptr;
	Death();
}