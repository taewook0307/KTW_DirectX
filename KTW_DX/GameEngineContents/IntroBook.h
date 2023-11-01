#pragma once

#define BOOKANIMATIONINTER 0.03f

class IntroBook : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroBook();
	~IntroBook();

	// delete Function
	IntroBook(const IntroBook& _Other) = delete;
	IntroBook(IntroBook&& _Other) noexcept = delete;
	IntroBook& operator=(const IntroBook& _Other) = delete;
	IntroBook& operator=(IntroBook&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> BookRenderer = nullptr;

	void Start() override;
};