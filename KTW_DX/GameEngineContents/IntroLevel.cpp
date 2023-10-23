#include "PreCompile.h"
#include "IntroLevel.h"

#include "IntroBook.h"

IntroLevel::IntroLevel()
{
}

IntroLevel::~IntroLevel()
{
}

void IntroLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Intro");

	Intro = CreateActor<IntroBook>(EUPDATEORDER::BackGround);
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Intro)
	{
		Intro->Death();
		Intro = nullptr;
	}

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Intro");
}