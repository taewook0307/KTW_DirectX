#pragma once

#define BOOKANIMATIONINTER 0.03f

#include <GameEngineCore/GameEngineActor.h>

class StoryBook : public GameEngineActor
{
public:
	// constrcuter destructer
	StoryBook();
	~StoryBook();

	// delete Function
	StoryBook(const StoryBook& _Other) = delete;
	StoryBook(StoryBook&& _Other) noexcept = delete;
	StoryBook& operator=(const StoryBook& _Other) = delete;
	StoryBook& operator=(StoryBook&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> BookRenderer = nullptr;

	void Start() override;
};