#pragma once

class Ocean : public GameEngineActor
{
public:
	// constrcuter destructer
	Ocean();
	~Ocean();

	// delete Function
	Ocean(const Ocean& _Other) = delete;
	Ocean(Ocean&& _Other) noexcept = delete;
	Ocean& operator=(const Ocean& _Other) = delete;
	Ocean& operator=(Ocean&& _Other) noexcept = delete;

	void SetOceanAnimation(int _Order, std::string_view _AniMationName, std::string_view _SpriteName, float _Inter = 0.1f, int _Start = -1, int _End = -1, bool _Loop = true);

	template<typename OrderType>
	void SetOceanAnimation(OrderType _Order, std::string_view _AniMationName, std::string_view _SpriteName, float _Inter = 0.1f, int _Start = -1, int _End = -1, bool _Loop = true)
	{
		SetOceanAnimation(static_cast<int>(_Order), _AniMationName, _SpriteName, _Inter, _Start, _End, _Loop);
	}

protected:
	std::shared_ptr<GameEngineSpriteRenderer> OceanRenderer = nullptr;

private:
};