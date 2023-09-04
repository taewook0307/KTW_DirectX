#include "PreCompile.h"
#include "PlayLevel.h"
#include "ContentsCore.h"

#include "BaseCharacter.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Character\\Normal");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	std::shared_ptr<BaseCharacter> NewPlayer = CreateActor<BaseCharacter>(UpdateOrder::Player);
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}