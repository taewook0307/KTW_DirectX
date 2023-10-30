#pragma once

#include <GameEngineCore/GameEngineActor.h>

class TestActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TestActor();
	~TestActor();

	// delete Function
	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> TestRenderer = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> HeadRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> TridentRenderer = nullptr;

	void Start() override;
};