#include "PreCompile.h"
#include "BaseLevel.h"

#include "OldFilm.h"
#include <GameEngineCore/BlurPostEffect.h>

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::Start()
{
	GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<OldFilm>();
	GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<BlurPostEffect>();
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Fade");
}