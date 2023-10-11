#pragma once

#include "BaseBoss.h"

class UvulaBoss : public BaseBoss
{
public:
	// constrcuter destructer
	UvulaBoss();
	~UvulaBoss();

	// delete Function
	UvulaBoss(const UvulaBoss& _Other) = delete;
	UvulaBoss(UvulaBoss&& _Other) noexcept = delete;
	UvulaBoss& operator=(const UvulaBoss& _Other) = delete;
	UvulaBoss& operator=(UvulaBoss&& _Other) noexcept = delete;

protected:

private:
	void StateUpdate(float _Delta);
	void ChangeState(EUVULABOSSSTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	EUVULABOSSSTATE CurState = EUVULABOSSSTATE::None;
	std::string State = "";

	std::shared_ptr<GameEngineSpriteRenderer> UvulaRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};