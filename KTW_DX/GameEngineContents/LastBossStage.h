#pragma once

#include "StageLevel.h"

#define SUMMONTIMER 5.0f

class LastBossStage : public StageLevel
{
public:
	// constrcuter destructer
	LastBossStage();
	~LastBossStage();

	// delete Function
	LastBossStage(const LastBossStage& _Other) = delete;
	LastBossStage(LastBossStage&& _Other) noexcept = delete;
	LastBossStage& operator=(const LastBossStage& _Other) = delete;
	LastBossStage& operator=(LastBossStage&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class BackGround> StageBackGround = nullptr;
	std::shared_ptr<class Map> StageMap = nullptr;
	std::shared_ptr<class DevilChair> BossChair = nullptr;
	std::shared_ptr<class Devil> Boss = nullptr;

	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	float SummonTimer = SUMMONTIMER;
	EACTORDIR SummonDir = EACTORDIR::Left;

	void CreateSummonDevil();
};