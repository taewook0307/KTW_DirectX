#include "PreCompile.h"
#include "TestLevel.h"

#include "Card.h"
#include "Map.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\Global\\UI\\Card");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageChair.png");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	float4 MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	GetMainCamera()->Transform.SetLocalPosition({ MapScale.Half().X, -(MapScale.Y - WinScale.Half().Y) });

	std::shared_ptr<Map> TempMap = CreateActor<Map>(EUPDATEORDER::Map);
	TempMap->MapInit("LastStagePixelMap.png");
	TempMap->PixelMapInit("LastStagePixelMap.png");
	TempMap->Transform.SetLocalPosition({ MapScale.Half().X, -MapScale.Half().Y });

	std::shared_ptr<Card> Check = CreateActor<Card>(EUPDATEORDER::UI);
	Check->Transform.SetLocalPosition({ 0.0f, 0.0f });
}

void TestLevel::Update(float _Delta)
{

}

void TestLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsSpriteManager::FolderSpriteRelease("Resources\\Texture\\Global\\UI\\Card");
}