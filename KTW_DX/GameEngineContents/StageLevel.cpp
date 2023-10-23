#include "PreCompile.h"
#include "StageLevel.h"

#include "StageStartUI.h"
#include "StageClearUI.h"
#include "StageFailUI.h"
#include "BaseCharacter.h"
#include "DebugWindow.h"

ESTAGERESULT StageLevel::StageResult = ESTAGERESULT::None;

StageLevel::StageLevel()
{
}

StageLevel::~StageLevel()
{
}

void StageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	// GameEngineGUI::CreateGUIWindow<DebugWindow>("Debug Tool");

	GameEngineInput::AddInputObject(this);

	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\StageEffect");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Character");

	CreateActor<StageStartUI>(EUPDATEORDER::UI);

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition({ 230.0f, -677.0f });
}

void StageLevel::Update(float _Delta)
{
	StageEnd(_Delta);
	ParryUpdate(_Delta);
}

void StageLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ResultUI = false;
	PhaseMoveTimer = PHASEMOVETIMER;
	StageResult = ESTAGERESULT::None;

	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\StageEffect");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character");
}

void StageLevel::StageEnd(float _Delta)
{
	if (ESTAGERESULT::Success == StageResult && false == ResultUI)
	{
		CreateActor<StageClearUI>(EUPDATEORDER::UI);
		ResultUI = true;
	}

	if (ESTAGERESULT::Fail == StageResult && false == ResultUI)
	{
		CreateActor<StageFailUI>(EUPDATEORDER::UI);
		ResultUI = true;
	}

	if (ESTAGERESULT::None != StageResult)
	{
		PhaseMoveTimer -= _Delta;
	}

	if (PhaseMoveTimer < 0.0f)
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
}

void StageLevel::ParryUpdate(float _Delta)
{
	if (0.0f > StopTimer)
	{
		StopTimer = STOPTIMER;
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
}