#pragma once

#include "StageLevel.h"

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
	void LastStageCameraMove(float _Delta);

private:
	std::shared_ptr<class BackGround> StageBackGround = nullptr;
	std::shared_ptr<class Map> StageMap = nullptr;
	std::shared_ptr<class Devil> Boss = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};