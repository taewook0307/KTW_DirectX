#pragma once

#include <GameEngineCore/GameEngineActor.h>

class MiniMapEnter : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMapEnter();
	~MiniMapEnter();

	// delete Function
	MiniMapEnter(const MiniMapEnter& _Other) = delete;
	MiniMapEnter(MiniMapEnter&& _Other) noexcept = delete;
	MiniMapEnter& operator=(const MiniMapEnter& _Other) = delete;
	MiniMapEnter& operator=(MiniMapEnter&& _Other) noexcept = delete;

	void EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName);

	inline void SetEnterLevel(std::string_view _EnterLevel)
	{
		EnterLevel = _EnterLevel;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> EnterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> EnterCollision = nullptr;
	std::string EnterLevel = "";

	void Start() override;
	void Update(float _Delta) override;
};