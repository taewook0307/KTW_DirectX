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

	void Start() override;
	void Update(float _Delta) override;
};