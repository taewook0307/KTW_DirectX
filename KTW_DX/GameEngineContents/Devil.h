#pragma once

#include "BaseBoss.h"

class Devil : public BaseBoss
{
public:
	// constrcuter destructer
	Devil();
	~Devil();

	// delete Function
	Devil(const Devil& _Other) = delete;
	Devil(Devil&& _Other) noexcept = delete;
	Devil& operator=(const Devil& _Other) = delete;
	Devil& operator=(Devil&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> DevilRenderer = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> EyeRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HeadRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> TridentRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	GameEngineState DevilState;
};