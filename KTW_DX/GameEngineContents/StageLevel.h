#pragma once

#define PHASEMOVETIMER 5.0f
#define STOPTIMER 0.3f

class StageLevel : public GameEngineLevel
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

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;

	void StageEnd(float _Delta);
	void ParryUpdate(float _Delta);
private:

	bool LevelStopToParry = false;
	float StopTimer = STOPTIMER;

	bool ResultUI = false;
};

