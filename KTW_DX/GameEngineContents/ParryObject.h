#pragma once

#include <GameEngineCore/GameEngineActor.h>

class ParryObject : public GameEngineActor
{
public:
	// constrcuter destructer
	ParryObject();
	~ParryObject();

	// delete Function
	ParryObject(const ParryObject& _Other) = delete;
	ParryObject(ParryObject&& _Other) noexcept = delete;
	ParryObject& operator=(const ParryObject& _Other) = delete;
	ParryObject& operator=(ParryObject&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> ParryRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> ParryCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};