﻿#include "PreCompile.h"
#include "StageLevel.h"

#include "StageStartUI.h"
#include "StageClearUI.h"
#include "StageFailUI.h"

ESTAGERESULT StageLevel::StageResult = ESTAGERESULT::None;

StageLevel::StageLevel()
{
}

StageLevel::~StageLevel()
{
}

void StageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineInput::AddInputObject(this);

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Global\\StageEffect");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	CreateActor<StageStartUI>(EUPDATEORDER::UI);
}

void StageLevel::Update(float _Delta)
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

void StageLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ResultUI = false;
	PhaseMoveTimer = PHASEMOVETIMER;
	StageResult = ESTAGERESULT::None;
}