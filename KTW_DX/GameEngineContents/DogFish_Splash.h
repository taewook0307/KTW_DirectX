#pragma once

#include <GameEngineCore/GameEngineActor.h>

class DogFish_Splash : public GameEngineActor
{
public:
	// constrcuter destructer
	DogFish_Splash();
	~DogFish_Splash();

	// delete Function
	DogFish_Splash(const DogFish_Splash& _Other) = delete;
	DogFish_Splash(DogFish_Splash&& _Other) noexcept = delete;
	DogFish_Splash& operator=(const DogFish_Splash& _Other) = delete;
	DogFish_Splash& operator=(DogFish_Splash&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
};