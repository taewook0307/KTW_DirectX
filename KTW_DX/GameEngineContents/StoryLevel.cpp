#include "PreCompile.h"
#include "StoryLevel.h"

#include "StoryBook.h"

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
	Dir.MoveChild("Resources\\Texture\\Level\\Story\\Start");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	Story = CreateActor<StoryBook>(UpdateOrder::BackGround);
}