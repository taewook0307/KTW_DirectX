#pragma once

#define PHASEMOVETIMER 5.0f
#define STOPTIMER 0.3f

#define HPUIPOSITION { -570.0f, -335.0f }

#include "BaseLevel.h"

class StageLevel : public BaseLevel
{
public:
	// constrcuter destructer
	StageLevel();
	~StageLevel();

	// delete Function
	StageLevel(const StageLevel& _Other) = delete;
	StageLevel(StageLevel&& _Other) noexcept = delete;
	StageLevel& operator=(const StageLevel& _Other) = delete;
	StageLevel& operator=(StageLevel&& _Other) noexcept = delete;

	static void StageClear()
	{
		if (ESTAGERESULT::None == StageResult)
		{
			StageResult = ESTAGERESULT::Success;
		}
	}

	static void StageFail()
	{
		if (ESTAGERESULT::None == StageResult)
		{
			StageResult = ESTAGERESULT::Fail;
		}
	}

	static ESTAGERESULT GetStageResult()
	{
		return StageResult;
	}

protected:
	static ESTAGERESULT StageResult;
	float PhaseMoveTimer = PHASEMOVETIMER;

	std::shared_ptr<class BaseCharacter> Player = nullptr;
	std::shared_ptr<class HpMarker> HpUI = nullptr;
	std::vector<std::shared_ptr<class Card>> AllCardUI;

	void CharacterResourcesLoad();

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Update(float _Delta) override;

	void StageEnd(float _Delta);
	void ParryUpdate(float _Delta);
	void AllCardUIAnimationChange();

	void LastLevelEnd(float _Delta);

	void PlayerUISetting();
	void PlayerUIDeath();

	float4 MapScale = float4::ZERO;
	float CameraSpeed = 100.0f;
	virtual float4 CameraMove(float _Delta);

private:
	bool LevelStopToParry = false;
	float StopTimer = STOPTIMER;

	bool ResultUI = false;

	bool IsFade = false;
	float LevelChangeTimer = 3.0f;

	std::shared_ptr<class FadePostEffect> FadeEffect = nullptr;

	bool CameraMovePossible(const float4& _CheckPos);
};

