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

	GameEngineSprite::Release("Page_12");
	GameEngineSprite::Release("Page_13");
	GameEngineSprite::Release("Page_14");
	GameEngineSprite::Release("Page_15");
	GameEngineSprite::Release("Page_16");
	GameEngineSprite::Release("Page_17");
	GameEngineSprite::Release("Page_18");

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Outro");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::string FileName = Files[i].GetFileName();
			GameEngineTexture::Release(FileName);
		}
	}
}