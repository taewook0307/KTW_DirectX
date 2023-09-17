#pragma once

#include "BaseActor.h"

class FirstBoss : public BaseActor
{
public:
	// constrcuter destructer
	FirstBoss();
	~FirstBoss();

	// delete Function
	FirstBoss(const FirstBoss& _Other) = delete;
	FirstBoss(FirstBoss&& _Other) noexcept = delete;
	FirstBoss& operator=(const FirstBoss& _Other) = delete;
	FirstBoss& operator=(FirstBoss&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> FirstBossRenderer = nullptr;

	ActorDir FirstBossDir = ActorDir::Left;

	void Start() override;
	void Update(float _Delta) override;

	void DirChange();
	void ChangeState(CharacterState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);
};