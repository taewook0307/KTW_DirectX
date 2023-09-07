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
		Path.MoveChild("Resources\\Texture\\Map\\Tutorial\\TutorialTestMap.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("TutorialTestMap.Png");
	}

	{
		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Texture\\Map\\Tutorial\\TutorialTestBitMap.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("TutorialTestBitMap.Png");
	}

	std::shared_ptr<BaseCharacter> NewPlayer = CreateActor<BaseCharacter>(UpdateOrder::Player);
	NewPlayer->Transform.SetLocalPosition({ 230.0f, -500.0f });

	TutorialMap = CreateActor<Map>(UpdateOrder::Map);
	TutorialMap->MapInit("TutorialTestMap.Png");
	TutorialMap->BitMapInit("TutorialTestBitMap.Png");

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialTestMap.Png");
	float4 SpriteHalfScale = Sprite->GetSpriteData(0).GetScale().Half();

	TutorialMap->Transform.SetLocalPosition({ SpriteHalfScale.X, -SpriteHalfScale.Y });
}
void TutorialStage::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_ESCAPE))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
}
