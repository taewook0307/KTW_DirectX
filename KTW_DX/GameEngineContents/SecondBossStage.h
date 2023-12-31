#pragma once

#include "StageLevel.h"

class SecondBossStage : public StageLevel
{
public:
	// constrcuter destructer
	SecondBossStage();
	~SecondBossStage();

	// delete Function
	SecondBossStage(const SecondBossStage& _Other) = delete;
	SecondBossStage(SecondBossStage&& _Other) noexcept = delete;
	SecondBossStage& operator=(const SecondBossStage& _Other) = delete;
	SecondBossStage& operator=(SecondBossStage&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class PirateBoss> PirateBossActor = nullptr;
	std::shared_ptr<class ShipBoss> ShipBossActor = nullptr;
	std::shared_ptr<class Barrel> BarrelActor = nullptr;
	std::shared_ptr<class Map> SecondStageMap = nullptr;
	std::shared_ptr<class UpperObject> MapUpper = nullptr;

	std::shared_ptr<class BackGround> Sky = nullptr;

	std::vector<std::shared_ptr<class Cloud>> Clouds;
	std::vector<std::shared_ptr<class Ocean>> Oceans;

	bool Phase3Start = false;

private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;
};