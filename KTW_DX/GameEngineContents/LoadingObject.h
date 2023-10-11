#pragma once

#include <GameEngineCore/GameEngineActor.h>

class LoadingObject : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingObject();
	~LoadingObject();

	// delete Function
	LoadingObject(const LoadingObject& _Other) = delete;
	LoadingObject(LoadingObject&& _Other) noexcept = delete;
	LoadingObject& operator=(const LoadingObject& _Other) = delete;
	LoadingObject& operator=(LoadingObject&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> LoadingObjectRenderer = nullptr;

	void Start() override;
};