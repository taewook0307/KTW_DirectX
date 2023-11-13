#pragma once

class Card : public GameEngineActor
{
public:
	// constrcuter destructer
	Card();
	~Card();

	// delete Function
	Card(const Card& _Other) = delete;
	Card(Card&& _Other) noexcept = delete;
	Card& operator=(const Card& _Other) = delete;
	Card& operator=(Card&& _Other) noexcept = delete;

protected:

private:
	float4 TextureScale = float4::ZERO;

	std::shared_ptr<GameEngineUIRenderer> CardRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	unsigned int CurHitCount = 0;
	unsigned int PrevHitCount = 0;
	void CardCharge();
};

