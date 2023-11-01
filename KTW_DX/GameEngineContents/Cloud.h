#pragma once

class Cloud : public GameEngineActor
{
public:
	// constrcuter destructer
	Cloud();
	~Cloud();

	// delete Function
	Cloud(const Cloud& _Other) = delete;
	Cloud(Cloud&& _Other) noexcept = delete;
	Cloud& operator=(const Cloud& _Other) = delete;
	Cloud& operator=(Cloud&& _Other) noexcept = delete;

	void SetCloud(int _Order, std::string_view _ImageName);

	template<typename OrderType>
	void SetCloud(OrderType _Order, std::string_view _ImageName)
	{
		SetCloud(static_cast<int>(_Order), _ImageName);
	}

	void SetCloudSpeed(float _Value)
	{
		CloudSpeed = _Value;
	}

protected:

private:
	float CloudSpeed = 0.5f;

	std::shared_ptr<GameEngineSpriteRenderer> CloudRenderer = nullptr;

	void Update(float _Delta) override;
};