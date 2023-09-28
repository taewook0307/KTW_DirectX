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
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Intro");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	Intro = CreateActor<IntroBook>(EUPDATEORDER::BackGround);
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Intro)
	{
		Intro->Death();
		Intro = nullptr;
	}

	GameEngineSprite::Release("Page_1");
	GameEngineSprite::Release("Page_2");
	GameEngineSprite::Release("Page_3");
	GameEngineSprite::Release("Page_4");
	GameEngineSprite::Release("Page_5");
	GameEngineSprite::Release("Page_6");
	GameEngineSprite::Release("Page_7");
	GameEngineSprite::Release("Page_8");
	GameEngineSprite::Release("Page_9");
	GameEngineSprite::Release("Page_10");
	GameEngineSprite::Release("Page_11");

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Intro");
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