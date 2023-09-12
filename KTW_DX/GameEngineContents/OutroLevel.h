#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class OutroLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	OutroLevel();
	~OutroLevel();

	// delete Function
	OutroLevel(const OutroLevel& _Other) = delete;
	OutroLevel(OutroLevel&& _Other) noexcept = delete;
	OutroLevel& operator=(const OutroLevel& _Other) = delete;
	OutroLevel& operator=(OutroLevel&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class OutroBook> Outro = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
};