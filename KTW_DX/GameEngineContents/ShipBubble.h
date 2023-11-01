#pragma once

#define SHIPBUBBLERENDERERPOS { 180.0f, 0.0f }
#define SHIPBUBBLECOLLISIONSCALE { 90.0f, 90.0f }

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
	void AppearStart();
	void MoveStart();
	void MoveUpdate(float _Delta);
	void PopStart();

private:
	float RotSpeed = 300.0f;
	float Speed = 200.0f;
	std::string State = "";
	ESHIPBUBBLESTATE CurState = ESHIPBUBBLESTATE::None;

	void StateUpdate(float _Delta);
	void ChangeState(ESHIPBUBBLESTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	std::shared_ptr<GameEngineSpriteRenderer> BubbleRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};