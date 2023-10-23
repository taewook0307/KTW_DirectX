#include "PreCompile.h"
#include "TestStage.h"

#include "BaseCharacter.h"
#include "ParryObject.h"
#include "Map.h"

TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

void TestStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineInput::AddInputObject(this);

	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Character");
	ContentsSpriteManager::CreateSingleSpriteDir("Resources\\Texture\\Tutorial");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Tutorial\\Parry");

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition(PLAYERSTARTPOS);

	TestParry = CreateActor<ParryObject>(EUPDATEORDER::Bullet);
	TestParry->Transform.SetLocalPosition({ 640.0f, -360.0f });

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TutorialMap.Png");
	float4 SpriteHalfScale = Sprite->GetSpriteData(0).GetScale().Half();

	TestMap = CreateActor<Map>(EUPDATEORDER::Map);
	TestMap->MapInit("TutorialMap.Png");
	TestMap->PixelMapInit("TutorialBitMap.Png");
	TestMap->Transform.SetLocalPosition({ SpriteHalfScale.X, -SpriteHalfScale.Y });
}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	if (nullptr != TestParry)
	{
		TestParry->Death();
		TestParry = nullptr;
	}

	if (nullptr != TestMap)
	{
		TestMap->Death();
		TestMap = nullptr;
	}
}

void TestStage::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('R', this))
	{
		TestParry->ParryActive();
	}

	if (0.0f > StopTimer)
	{
		StopTimer = 0.3f;
		LevelStopToParry = false;
		BaseCharacter::MainCharacter->ParrySuccessReset();
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);
	}

	if (true == BaseCharacter::MainCharacter->GetParrySuccess())
	{
		LevelStopToParry = true;
		GameEngineCore::MainTime.SetAllTimeScale(0.0f);
	}

	if (true == LevelStopToParry)
	{
		StopTimer -= _Delta;
	}

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character");
	ContentsSpriteManager::SingleSpriteInDirRelease("Resources\\Texture\\Tutorial");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Tutorial\\Parry");
}