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
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Outro");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	Outro = CreateActor<OutroBook>(UpdateOrder::BackGround);
}

void OutroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Outro)
	{
		Outro->Death();
		Outro = nullptr;
	}
}