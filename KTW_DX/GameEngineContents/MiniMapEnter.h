#pragma once

class MiniMapEnter : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMapEnter();
	~MiniMapEnter();

	// delete Function
	MiniMapEnter(const MiniMapEnter& _Other) = delete;
	MiniMapEnter(MiniMapEnter&& _Other) noexcept = delete;
	MiniMapEnter& operator=(const MiniMapEnter& _Other) = delete;
	MiniMapEnter& operator=(MiniMapEnter&& _Other) noexcept = delete;

	void EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName);
	void EnterSpriteInit(std::string_view _FileName, int _Order = 0);

	void SetCollisionScaleAndPosition(float4 _Scale = float4::ONE, float4 _Position = float4::ZERO);

	inline void SetEnterLevel(std::string_view _EnterLevel)
	{
		EnterLevel = _EnterLevel;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> MiniMapEnterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MiniMapEnterCollision = nullptr;
	std::string EnterLevel = "";

	void Start() override;
	void Update(float _Delta) override;
};