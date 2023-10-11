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
	LoadingObjectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UI);
	LoadingObjectRenderer->CreateAnimation("Loading", "LoadingTimer", 0.05f);
	LoadingObjectRenderer->ChangeAnimation("Loading");
	LoadingObjectRenderer->AutoSpriteSizeOn();
}