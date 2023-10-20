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

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Intro");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
	{
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			std::string Check = Dir.GetFileName();
			GameEngineSprite::Release(Dir.GetFileName());
		}
	}

	{
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
}