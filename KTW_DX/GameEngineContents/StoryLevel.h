#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class StoryLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StoryLevel();
	~StoryLevel();

	// delete Function
	StoryLevel(const StoryLevel& _Other) = delete;
	StoryLevel(StoryLevel&& _Other) noexcept = delete;
	StoryLevel& operator=(const StoryLevel& _Other) = delete;
	StoryLevel& operator=(StoryLevel&& _Other) noexcept = delete;

protected:

private:

	std::shared_ptr<class StoryBook> Story = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;

};