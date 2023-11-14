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
#include "Card.h"

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
	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\Global\\UI\\Card");

	std::shared_ptr<FadeObject> FadeEffect = CreateActor<FadeObject>(EUPDATEORDER::UI);
	FadeEffect->SetFadeType(true);
	
	CreateActor<StageStartUI>(EUPDATEORDER::UI);

	Player = CreateActor<BaseCharacter>(EUPDATEORDER::Player);
	Player->Transform.SetLocalPosition({ 230.0f, -677.0f });

	PlayerUISetting();
}

void StageLevel::Update(float _Delta)
{
	StageEnd(_Delta);
	ParryUpdate(_Delta);
	AllCardUIAnimationChange();
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

	if (nullptr != FadeEffect)
	{
		FadeEffect->Death();
		FadeEffect = nullptr;
	}

	PlayerUIDeath();

	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\StageEffect");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character\\CupHead");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\Character\\Bullet");
	ContentsSpriteManager::SpriteAndTextureInAllDirRelease("Resources\\Texture\\Global\\UI\\HpMarker");
	ContentsSpriteManager::FolderSpriteRelease("Resources\\Texture\\Global\\UI\\Card");
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
		FadeEffect = GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
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

void StageLevel::PlayerUISetting()
{
	HpUI = CreateActor<HpMarker>(EUPDATEORDER::UI);
	HpUI->Transform.SetLocalPosition(HPUIPOSITION);

	AllCardUI.resize(5);

	AllCardUI[0] = CreateActor<Card>(EUPDATEORDER::UI);
	AllCardUI[0]->Transform.SetLocalPosition({ -510.0f, -350.0f });

	AllCardUI[1] = CreateActor<Card>(EUPDATEORDER::UI);
	AllCardUI[1]->Transform.SetLocalPosition({ -490.0f, -350.0f });
	AllCardUI[1]->SetHitSuccessFirstValue(100);

	AllCardUI[2] = CreateActor<Card>(EUPDATEORDER::UI);
	AllCardUI[2]->Transform.SetLocalPosition({ -470.0f, -350.0f });
	AllCardUI[2]->SetHitSuccessFirstValue(200);

	AllCardUI[3] = CreateActor<Card>(EUPDATEORDER::UI);
	AllCardUI[3]->Transform.SetLocalPosition({ -450.0f, -350.0f });
	AllCardUI[3]->SetHitSuccessFirstValue(300);

	AllCardUI[4] = CreateActor<Card>(EUPDATEORDER::UI);
	AllCardUI[4]->Transform.SetLocalPosition({ -430.0f, -350.0f });
	AllCardUI[4]->SetHitSuccessFirstValue(400);
}

void StageLevel::PlayerUIDeath()
{
	if (nullptr != HpUI)
	{
		HpUI->Death();
		HpUI = nullptr;
	}

	for (size_t i = 0; i < AllCardUI.size(); i++)
	{
		AllCardUI[i]->Death();
		AllCardUI[i] = nullptr;
	}

	AllCardUI.clear();
}

void StageLevel::AllCardUIAnimationChange()
{
	int CharacterHitSuccess = Player->GetHitSuccess();

	if (500 <= CharacterHitSuccess)
	{
		for (size_t i = 0; i < AllCardUI.size(); i++)
		{
			AllCardUI[i]->ChangeLoopAnimation();
		}
	}
}

float4 StageLevel::CameraMove(float _Delta)
{
	float4 CameraPos = GetMainCamera()->Transform.GetWorldPosition();
	float4 WinScaleQuarter = GameEngineCore::MainWindow.GetScale().Half().Half();

	float4 PlayerPos = Player->Transform.GetWorldPosition();

	float4 MovePos = float4::ZERO;

	if (PlayerPos.X < CameraPos.X - WinScaleQuarter.X)
	{
		MovePos = float4::LEFT * _Delta * CameraSpeed;
	}
	else if (PlayerPos.X > CameraPos.X + WinScaleQuarter.X)
	{
		MovePos = float4::RIGHT * _Delta * CameraSpeed;
	}
	else
	{
		return float4::ZERO;
	}

	float4 CheckPos = CameraPos + MovePos;

	if (true == CameraMovePossible(CheckPos))
	{
		GetMainCamera()->Transform.AddLocalPosition(MovePos);
	}
	else
	{
		return float4::ZERO;
	}

	return MovePos;
}

bool StageLevel::CameraMovePossible(const float4& _CheckPos)
{
	if (float4::ZERO == MapScale)
	{
		MsgBoxAssert("맵 크기가 지정되지 않았습니다");
		return false;
	}

	float4 CameraPos = _CheckPos;
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();

	float LeftX = CameraPos.X - WinScaleHalf.X;
	float RightX = CameraPos.X + WinScaleHalf.X;

	if (LeftX <= 0.0f)
	{
		return false;
	}

	if (RightX >= MapScale.X)
	{
		return false;
	}

	return true;
}