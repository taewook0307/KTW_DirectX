#include "PreCompile.h"
#include "LoadingObject.h"

LoadingObject::LoadingObject()
{
}

LoadingObject::~LoadingObject()
{
}

void LoadingObject::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UI);
	Renderer->CreateAnimation("Loading", "LoadingTimer", 0.05f);
	Renderer->ChangeAnimation("Loading");
	Renderer->AutoSpriteSizeOn();
}