#pragma once

#define BOOKANIMATIONINTER 0.03f

#include <GameEngineCore/GameEngineActor.h>

class OutroBook : public GameEngineActor
{
public:
	// constrcuter destructer
	OutroBook();
	~OutroBook();

	// delete Function
	OutroBook(const OutroBook& _Other) = delete;
	OutroBook(OutroBook&& _Other) noexcept = delete;
	OutroBook& operator=(const OutroBook& _Other) = delete;
	OutroBook& operator=(OutroBook&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> BookRenderer = nullptr;

	void Start() override;
};