#pragma once

class WorldMapFlag : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapFlag();
	~WorldMapFlag();

	// delete Function
	WorldMapFlag(const WorldMapFlag& _Other) = delete;
	WorldMapFlag(WorldMapFlag&& _Other) noexcept = delete;
	WorldMapFlag& operator=(const WorldMapFlag& _Other) = delete;
	WorldMapFlag& operator=(WorldMapFlag&& _Other) noexcept = delete;

	void ChangeStayStateFlag()
	{
		FlagState.ChangeState(EWorldMapFlag::Stay);
		return;
	}

	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return FlagRenderer->IsCurAnimation(_AnimationName);
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> FlagRenderer = nullptr;
	GameEngineState FlagState;

	void Start() override;
	void Update(float _Delta) override;
};