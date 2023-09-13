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

	// 캐릭터와 Parry를 성공했는지 여부
	void ParryOn()
	{
		Parry = true;
	}

	void ParryOff()
	{
		Parry = false;
	}

	bool GetParry() const
	{
		return Parry;
	}

protected:

private:
	bool ParryActivation = false;
	bool Parry = false;

	std::shared_ptr<GameEngineSpriteRenderer> ParryRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> ParryCollision = nullptr;

	std::vector<std::shared_ptr<GameEngineCollision>> ParryCol;

	void Start() override;
	void Update(float _Delta) override;
};