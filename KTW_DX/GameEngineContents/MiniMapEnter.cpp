#include "PreCompile.h"
#include "MiniMapEnter.h"

MiniMapEnter::MiniMapEnter()
{
}

MiniMapEnter::~MiniMapEnter()
{
}

void MiniMapEnter::Start()
{
	EnterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Map);
}

void MiniMapEnter::Update(float _Delta)
{

}

void MiniMapEnter::EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName)
{
	EnterRenderer->CreateAnimation(_AnimationName, _SpriteName);
	EnterRenderer->ChangeAnimation(_AnimationName);
	EnterRenderer->AutoSpriteSizeOn();
}