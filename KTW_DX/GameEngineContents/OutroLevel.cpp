#include "PreCompile.h"
#include "OutroLevel.h"

#include "OutroBook.h"

OutroLevel::OutroLevel()
{
}

OutroLevel::~OutroLevel()
{
}

void OutroLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Intro\\cutscene_pageturn_01.wav");
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Intro\\cutscene_pageturn_02.wav");
	ContentsResourcesManager::SoundLoad("Resources\\Sound\\Intro\\cutscene_pageturn_03.wav");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\Outro");

	Outro = CreateActor<OutroBook>(EUPDATEORDER::BackGround);
}

void OutroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Outro)
	{
		Outro->Death();
		Outro = nullptr;
	}

	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Outro");
}