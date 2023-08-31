#include "PreCompile.h"
#include "StoryLevel.h"

#include "BackGround.h"

StoryLevel::StoryLevel()
{
}

StoryLevel::~StoryLevel()
{
}

void StoryLevel::Start()
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
	StoryAnimation->AnimationInit("StoryPage_1", "Page_1");
}

void StoryLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsPress('Z'))
	{
		GameEngineCore::ChangeLevel("StoryLevel");
	}
}