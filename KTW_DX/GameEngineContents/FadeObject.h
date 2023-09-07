#pragma once

#include <GameEngineCore/GameEngineActor.h>

class FadeObject : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeObject();
	~FadeObject();

	// delete Function
	FadeObject(const FadeObject& _Other) = delete;
	FadeObject(FadeObject&& _Other) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

	inline bool GetFadeAnimationEnd()
	{
		return FadeRenderer->IsCurAnimationEnd();
	}
	
	void SetFadeType(bool _FadeIn = false);

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;

	void Start() override;
};