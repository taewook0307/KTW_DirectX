#pragma once

class WorldMapCharacter_RunDust : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapCharacter_RunDust();
	~WorldMapCharacter_RunDust();

	// delete Function
	WorldMapCharacter_RunDust(const WorldMapCharacter_RunDust& _Other) = delete;
	WorldMapCharacter_RunDust(WorldMapCharacter_RunDust&& _Other) noexcept = delete;
	WorldMapCharacter_RunDust& operator=(const WorldMapCharacter_RunDust& _Other) = delete;
	WorldMapCharacter_RunDust& operator=(WorldMapCharacter_RunDust&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> DustRenderer = nullptr;
};

