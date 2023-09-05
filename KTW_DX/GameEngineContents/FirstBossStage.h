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
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class Map> StageMap = nullptr;
};