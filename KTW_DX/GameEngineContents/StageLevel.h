#pragma once

#define PHASEMOVETIMER 5.0f
#define STOPTIMER 0.3f

#define HPUIPOSITION { -590.0f, -350.0f }

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

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void LastLevelEnd(float _Delta);

	void Update(float _Delta) override;

	void StageEnd(float _Delta);
	void ParryUpdate(float _Delta);

	template<typename ActorType, typename EnumType>
	void AllRemainActorDeath(EnumType _UpdateOrder)
	{
		std::vector<std::shared_ptr<ActorType>> RemainActors = GetObjectGroupConvert<ActorType>(_UpdateOrder);

		if (0 == RemainActors.size())
		{
			return;
		}

		for (size_t i = 0; i < RemainActors.size(); i++)
		{
			RemainActors[i]->Death();
		}
	}

private:
	bool LevelStopToParry = false;
	float StopTimer = STOPTIMER;

	bool ResultUI = false;
};

