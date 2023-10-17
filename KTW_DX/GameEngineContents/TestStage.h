#pragma once

#include <GameEngineCore/GameEngineLevel.h>

#define PLAYERSTARTPOS { 230.0f, - 605.0f }

class TestStage : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestStage();
	~TestStage();

	// delete Function
	TestStage(const TestStage& _Other) = delete;
	TestStage(TestStage&& _Other) noexcept = delete;
	TestStage& operator=(const TestStage& _Other) = delete;
	TestStage& operator=(TestStage&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class BaseCharacter> Player = nullptr;
	std::shared_ptr<class ParryObject> TestParry = nullptr;
	std::shared_ptr<class Map> TestMap = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;
};