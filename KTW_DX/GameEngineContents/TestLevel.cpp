#include "PreCompile.h"
#include "TestLevel.h"

#include "BackGround.h"
#include "Lava.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\BackGround\\LastStageBackGround.png");
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\BackGround\\Lava");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	float4 MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	float4 WinScaleHalf = WinScale.Half();

	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	std::shared_ptr<BackGround> TempBack = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TempBack->BackGroundInitAuto("LastStageBackGround.png");
	TempBack->Transform.SetLocalPosition({ MapScale.Half().X, -WinScaleHalf.Y });

	std::shared_ptr<Lava> TestLava = CreateActor<Lava>(EUPDATEORDER::BackGround);
	TestLava->Transform.SetLocalPosition({ 265.0f, -255.0f });

	std::shared_ptr<Lava> TestLavaB = CreateActor<Lava>(EUPDATEORDER::BackGround);
	TestLavaB->Transform.SetLocalPosition({ 1155.0f, -215.0f });
	TestLavaB->ChagneLavaType();
}

void TestLevel::Update(float _Delta)
{

}

void TestLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsResourcesManager::SingleSpriteRelease("Resources\\Texture\\LastBossStage\\BackGround\\LastStageBackGround.png");
	ContentsResourcesManager::SingleSpriteRelease("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\BackGround\\Lava");
}