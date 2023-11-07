#include "PreCompile.h"
#include "TestLevel.h"

#include "SummonDevil.h"
#include "DevilChair.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\LastBossStage\\SummonDevil");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStagePixelMap.png");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\LastBossStage\\Map\\LastStageChair.png");

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find("LastStagePixelMap.png");
	float4 MapScale = MapTexture->GetScale();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	GetMainCamera()->Transform.SetLocalPosition({ 640.0f, -380.0f });

	std::shared_ptr<DevilChair> BossChair = CreateActor<DevilChair>(EUPDATEORDER::Map);
	BossChair->Transform.SetLocalPosition({ MapScale.Half().X, -WinScale.Y + 80.0f });

	std::shared_ptr<SummonDevil> Check = CreateActor<SummonDevil>(EUPDATEORDER::Monster);
	Check->Transform.SetLocalPosition({ 530.0f, -610.0f });
}

void TestLevel::Update(float _Delta)
{

}

void TestLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\LastBossStage\\SummonDevil");
}