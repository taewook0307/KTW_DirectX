#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class FirstBossStage : public GameEngineLevel
{
public:
	// constrcuter destructer
	FirstBossStage();
	~FirstBossStage();

	// delete Function
	FirstBossStage(const FirstBossStage& _Other) = delete;
	FirstBossStage(FirstBossStage&& _Other) noexcept = delete;
	FirstBossStage& operator=(const FirstBossStage& _Other) = delete;
	FirstBossStage& operator=(FirstBossStage&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class Map> StageMap = nullptr;
	std::shared_ptr<class UpperObject> StageMapUpper = nullptr;
	std::shared_ptr<class BaseCharacter> Player = nullptr;
	std::shared_ptr<class FirstBoss> Boss = nullptr;
	std::shared_ptr<class FirstBossPhase3> BossPhase3 = nullptr;
	std::shared_ptr<class StageClearUI> ClearUI = nullptr;

	bool Phase3Start = false;
	bool Phase3End = false;
	float Phase3Timer = 5.0f;
	float PhaseMoveTimer = 5.0f;

private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;
};