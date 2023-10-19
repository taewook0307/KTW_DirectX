#pragma once

#include <GameEngineCore/GameEngineActor.h>

class MiniMapFlag : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMapFlag();
	~MiniMapFlag();

	// delete Function
	MiniMapFlag(const MiniMapFlag& _Other) = delete;
	MiniMapFlag(MiniMapFlag&& _Other) noexcept = delete;
	MiniMapFlag& operator=(const MiniMapFlag& _Other) = delete;
	MiniMapFlag& operator=(MiniMapFlag&& _Other) noexcept = delete;

	void ChangeStayStateFlag()
	{
		FlagState.ChangeState(EMINIMAPFLAG::Stay);
		return;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> FlagRenderer = nullptr;
	GameEngineState FlagState;

	void Start() override;
	void Update(float _Delta) override;
};