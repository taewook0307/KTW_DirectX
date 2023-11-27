#pragma once

class WorldMapEnter : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapEnter();
	~WorldMapEnter();

	// delete Function
	WorldMapEnter(const WorldMapEnter& _Other) = delete;
	WorldMapEnter(WorldMapEnter&& _Other) noexcept = delete;
	WorldMapEnter& operator=(const WorldMapEnter& _Other) = delete;
	WorldMapEnter& operator=(WorldMapEnter&& _Other) noexcept = delete;

	void EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName);
	void EnterSpriteInit(std::string_view _FileName, int _Order = 0);

	void SetCollisionScaleAndPosition(float4 _Scale = float4::ONE, float4 _Position = float4::ZERO);

	inline void SetEnterLevel(std::string_view _EnterLevel)
	{
		EnterLevel = _EnterLevel;
	}

	void LevelChangeSoundOn()
	{
		LevelChangeSound = true;
	}

	void LevelChangeSoundOff()
	{
		LevelChangeSound = false;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> WorldMapEnterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> WorldMapEnterCollision = nullptr;
	std::shared_ptr<class FadeObject> FadeEffect = nullptr;
	std::string EnterLevel = "";

	bool LevelChangeSound = true;

	void Start() override;
	void Update(float _Delta) override;
};