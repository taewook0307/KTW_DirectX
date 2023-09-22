#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class SecondBossStage : public GameEngineLevel
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
	void Update(float _Delta) override;
};