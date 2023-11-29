#include "PreCompile.h"
#include "TestLevel.h"

#include "BackGround.h"
#include "Lava.h"
#include "Smoke.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsResourcesManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\BackGround\\Lava");
	ContentsResourcesManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\BackGround\\Smoke");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	float4 MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	GetMainCamera()->Transform.SetLocalPosition({ MapScale.Half().X, -(MapScale.Y - WinScale.Half().Y) });

	std::shared_ptr<BackGround> TempBack = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TempBack->BackGroundInit("LastStagePixelMap.png");
	TempBack->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	std::shared_ptr<Lava> TestLava = CreateActor<Lava>(EUPDATEORDER::BackGround);
	TestLava->Transform.SetLocalPosition({ MapScale.Half().X, -(MapScale.Y - WinScale.Half().Y) });

	std::shared_ptr<Smoke> TestSmoke = CreateActor<Smoke>(EUPDATEORDER::BackGround);
	TestSmoke->Transform.SetLocalPosition({ MapScale.Half().X, -(MapScale.Y - WinScale.Half().Y) });
}

void TestLevel::Update(float _Delta)
{

}

void TestLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsResourcesManager::SingleSpriteRelease("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\BackGround\\Lava");
	ContentsResourcesManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\BackGround\\Smoke");
}