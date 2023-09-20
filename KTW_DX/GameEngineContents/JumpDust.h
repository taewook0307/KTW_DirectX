#pragma once

#include <GameEngineCore/GameEngineActor.h>

class JumpDust : public GameEngineActor
{
public:
	// constrcuter destructer
	JumpDust();
	~JumpDust();

	// delete Function
	JumpDust(const JumpDust& _Other) = delete;
	JumpDust(JumpDust&& _Other) noexcept = delete;
	JumpDust& operator=(const JumpDust& _Other) = delete;
	JumpDust& operator=(JumpDust&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	void Start() override;
};