#include "PreCompile.h"
#include "TutorialStage.h"

#include "Map.h"
#include "BaseCharacter.h"

TutorialStage::TutorialStage()
{
}

TutorialStage::~TutorialStage()
{
}

void TutorialStage::LevelStart(GameEngineLevel* _PrevLevel)
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
		Path.MoveChild("Resources\\Texture\\Map\\Tutorial\\TutorialMap.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("TutorialMap.Png");
	}

	{
		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Texture\\Map\\Tutorial\\TutorialBitMap.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("TutorialBitMap.Png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\BUllet");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	Player = CreateActor<BaseCharacter>(UpdateOrder::Player);
	Player->Transform.SetLocalPosition({ 230.0f, -500.0f });

	TutorialMap = CreateActor<Map>(UpdateOrder::Map);
	TutorialMap->MapInit("TutorialMap.Png");
	TutorialMap->BitMapInit("TutorialBitMap.Png");

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialMap.Png");
	float4 SpriteHalfScale = Sprite->GetSpriteData(0).GetScale().Half();

	TutorialMap->Transform.SetLocalPosition({ SpriteHalfScale.X, -SpriteHalfScale.Y });
}
void TutorialStage::Update(float _Delta)
{
	GetMainCamera()->Transform.SetLocalPosition(Player->Transform.GetWorldPosition());

	if (true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
}
