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

	void SetHitSuccessFirstValue(unsigned int _Value)
	{
		CurHitSuccess = _Value;
		PrevHitSuccess = _Value;
		InitialValue = _Value;
	}

	void ChangeLoopAnimation()
	{
		CardRenderer->ChangeAnimation("Card_Loop");
		return;
	}

protected:

private:
	float4 TextureScale = float4::ZERO;

	std::shared_ptr<GameEngineUIRenderer> CardRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	unsigned int CurHitSuccess = 0;
	unsigned int PrevHitSuccess = 0;
	unsigned int InitialValue = 0;
	void CardCharge();
	void CardRendererReset();
	void CardReset();
	void CardAdjust();

	void CardAnimationChange();
};

