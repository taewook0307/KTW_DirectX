#pragma once

class Map : public GameEngineActor
{
public:
	friend class DebugWindow;
	static Map* MainMap;

	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void MapInit(std::string_view _SpriteName);
	void PixelMapInit(std::string_view _SpriteName);
	void MapAnimationInit(std::string_view _AnimationName, std::string_view _FileName, float _Inter = 0.1f, bool _Loop = true, bool _SizeFixWindow = true, unsigned int _Start = -1, unsigned int _End = -1);

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor);

	bool GetPixelMapRenderSwitch()
	{
		return PixelMapRenderSwitch;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> MapRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> PixelMapRenderer = nullptr;

	std::string PixelMapFileName = "";

	bool PixelMapRenderSwitch = false;

	void Start() override;
	void Update(float _Delta) override;

	void RendererSwitch();
};