#include "PreCompile.h"
#include "StageLevel.h"

#include "FadeObject.h"
#include "StageStartUI.h"
#include "StageClearUI.h"
#include "StageFailUI.h"

#include "BaseCharacter.h"
#include "RunDust.h"
#include "JumpDust.h"
#include "DashDust.h"
#include "ParryEffect.h"
#include "SpecialAttackDust.h"

#include "HpMarker.h"

#include "DebugWindow.h"

#include <GameEngineCore/FadePostEffect.h>

ESTAGERESULT StageLevel::StageResult = ESTAGERESULT::None;

StageLevel::StageLevel()
{
}

StageLevel::~StageLevel()
{
}

void StageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//GameEngineGUI::CreateGUIWindow<DebugWindow>("Debug Tool");

	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\StageEffect");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Character\\CupHead");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Character\\Bullet");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\UI\\HpMarker");

	std::shared_ptr<FadeObject> FadeEffect = CreateActor<FadeObject>(EUPDATEORDER::UI);
	FadeEffect->SetFadeType(true);
	
	CreateActor<StageStartUI>(EUPDATEORDER::UI);

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition({ 230.0f, -677.0f });

	HpUI = CreateActor<HpMarker>(EUPDATEORDER::UI);
	HpUI->Transform.SetLocalPosition(HPUIPOSITION);
}

void StageLevel::Update(float _Delta)
{
	StageEnd(_Delta);
	ParryUpdate(_Delta);
}

void StageLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllRemainActorDeath<StageStartUI>(EUPDATEORDER::UI);
	AllRemainActorDeath<StageClearUI>(EUPDATEORDER::UI);
	AllRemainActorDeath<StageFailUI>(EUPDATEORDER::UI);
	AllRemainActorDeath<RunDust>(EUPDATEORDER::Effect);
	AllRemainActorDeath<JumpDust>(EUPDATEORDER::Effect);
	AllRemainActorDeath<DashDust>(EUPDATEORDER::Effect);
	AllRemainActorDeath<ParryEffect>(EUPDATEORDER::Effect);
	AllRemainActorDeath<SpecialAttackDust>(EUPDATEORDER::Effect);

	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
		BaseCharacter::MainCharacter->Death();
		BaseCharacter::MainCharacter = nullptr;
	}

	if (nullptr != HpUI)
	{
		HpUI->Death();
		HpUI = nullptr;
	}

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\StageEffect");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character\\CupHead");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character\\Bullet");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\UI\\HpMarker");
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
		ResultUI = false;
		PhaseMoveTimer = PHASEMOVETIMER;
		StageResult = ESTAGERESULT::None;
		IsFade = true;
		GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
	}

	if (true == IsFade)
	{
		LevelChangeTimer -= _Delta;
	}

	if (0.0f > LevelChangeTimer)
	{
		IsFade = false;
		LevelChangeTimer = 3.0f;
		GameEngineCore::ChangeLevel("WorldMapLevel");
	}
}

void StageLevel::LastLevelEnd(float _Delta)
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

	if (PhaseMoveTimer < 0.0f && ESTAGERESULT::Success == StageResult)
	{
		GameEngineCore::ChangeLevel("OutroLevel");
	}
	else if(PhaseMoveTimer < 0.0f && ESTAGERESULT::Fail == StageResult)
	{
		GameEngineCore::ChangeLevel("WorldMapLevel");
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