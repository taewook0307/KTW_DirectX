#include "PreCompile.h"
#include "PlayLevel.h"
#include "ContentsCore.h"
#include "Player.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Start()
{
	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
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

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(UpdateOrder::Player);
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}