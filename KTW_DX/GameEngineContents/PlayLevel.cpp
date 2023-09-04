#include "PreCompile.h"
#include "PlayLevel.h"
#include "ContentsCore.h"

#include "BaseCharacter.h"
#include "Map.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::Start()
{
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

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

	{
		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Texture\\Map\\TestMap.Png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("TestMap.Png");
	}

	std::shared_ptr<BaseCharacter> NewPlayer = CreateActor<BaseCharacter>(UpdateOrder::Player);
	NewPlayer->Transform.SetLocalPosition({ WinScaleHalf.X, 0.0f });

	std::shared_ptr<Map> TestMap = CreateActor<Map>(UpdateOrder::Map);
	TestMap->MapInit("TestMap.Png");
	TestMap->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}