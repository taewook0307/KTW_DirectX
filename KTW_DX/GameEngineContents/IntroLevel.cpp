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
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Intro\\cutscene_pageturn_01.wav");
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Intro\\cutscene_pageturn_02.wav");
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Intro\\cutscene_pageturn_03.wav");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\Intro");

	BGMPlayer = GameEngineSound::SoundPlay("03 Introduction.mp3");

	Intro = CreateActor<IntroBook>(EUPDATEORDER::BackGround);
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();

	if (nullptr != Intro)
	{
		Intro->Death();
		Intro = nullptr;
	}

	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Intro");
}