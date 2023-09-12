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
	Dir.MoveChild("Resources\\Texture\\Level\\Story\\Start");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	Intro = CreateActor<IntroBook>(UpdateOrder::BackGround);
}