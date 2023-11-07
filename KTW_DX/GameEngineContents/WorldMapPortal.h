#pragma once

#define PORTALCOLLISIONSCALE { 35.0f, 72.0f }

class WorldMapPortal : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapPortal();
	~WorldMapPortal();

	// delete Function
	WorldMapPortal(const WorldMapPortal& _Other) = delete;
	WorldMapPortal(WorldMapPortal&& _Other) noexcept = delete;
	WorldMapPortal& operator=(const WorldMapPortal& _Other) = delete;
	WorldMapPortal& operator=(WorldMapPortal&& _Other) noexcept = delete;

	float4 GetDestination()
	{
		return Destination;
	}

	void SetDestination(const float4& _Destination)
	{
		Destination = _Destination;
	}

	void DestinationReset()
	{
		Destination = float4::ZERO;
	}

	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return PortalRenderer->IsCurAnimation(_AnimationName);
	}

protected:

private:

	float4 Destination = float4::ZERO;

	std::shared_ptr<GameEngineSpriteRenderer> PortalRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PortalCollision = nullptr;

	void Start() override;
	// void Update(float _Delta) override;
};