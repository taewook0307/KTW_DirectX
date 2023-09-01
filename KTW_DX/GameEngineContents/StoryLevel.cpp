#include "PreCompile.h"
#include "StoryLevel.h"

#include "BackGround.h"

StoryLevel::StoryLevel()
{
}

StoryLevel::~StoryLevel()
{
}

void StoryLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Level\\Story");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	StoryAnimation = CreateActor<BackGround>(UpdateOrder::BackGround);
	StoryAnimation->AnimationInit("StoryPage_1", "Page_1", 0.05f, false);
}

void StoryLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsPress('Z'))
	{
		if (AnimationNumber < 13)
		{
			++AnimationNumber;
			ChangeStoryAnimation();
		}
		else
		{
			GameEngineCore::ChangeLevel("MiniMapLevel");
		}
		
	}
}

void StoryLevel::ChangeStoryAnimation()
{
	std::string AnimationName = "StoryPage_" + std::to_string(AnimationNumber);
	std::string FolderName = "Page_" + std::to_string(AnimationNumber);

	StoryAnimation->AnimationInit(AnimationName, FolderName, 0.05f, false);
}