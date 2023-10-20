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

	// Parry 활성화 여부
	void ParryActive()
	{
		ParryActivation = true;
	}

	void ParryInactive()
	{
		ParryActivation = false;
	}

	bool GetParryActivation() const
	{
		return ParryActivation;
	}

protected:
	bool ParryActivation = true;

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> ParryCollision = nullptr;
private:
};