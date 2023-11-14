#pragma once

#include "StageLevel.h"

#define PHASE3TIMER 5.0f

class FirstBossStage : public StageLevel
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
	std::shared_ptr<class BackGround> StageBackGround = nullptr;
	std::shared_ptr<class Map> StageMap = nullptr;
	std::shared_ptr<class UpperObject> StageMapUpper = nullptr;
	std::shared_ptr<class FirstBoss> Boss = nullptr;
	std::shared_ptr<class FirstBossPhase3> BossPhase3 = nullptr;

	bool Phase3Start = false;
	float Phase3Timer = PHASE3TIMER;

private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;
};