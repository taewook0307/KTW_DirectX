#pragma once

#include <GameEngineCore/GameEngineActor.h>

class ShipBubble : public GameEngineActor
{
public:
	// constrcuter destructer
	ShipBubble();
	~ShipBubble();

	// delete Function
	ShipBubble(const ShipBubble& _Other) = delete;
	ShipBubble(ShipBubble&& _Other) noexcept = delete;
	ShipBubble& operator=(const ShipBubble& _Other) = delete;
	ShipBubble& operator=(ShipBubble&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> BubbleRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};