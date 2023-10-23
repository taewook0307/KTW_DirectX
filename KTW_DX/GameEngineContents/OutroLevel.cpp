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
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Outro");

	Outro = CreateActor<OutroBook>(EUPDATEORDER::BackGround);
}

void OutroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Outro)
	{
		Outro->Death();
		Outro = nullptr;
	}

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Outro");
}