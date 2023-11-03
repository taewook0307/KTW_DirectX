#pragma once

#define PORTALCOLLISIONSCALE { 35.0f, 72.0f }

class MiniMapPortal : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMapPortal();
	~MiniMapPortal();

	// delete Function
	MiniMapPortal(const MiniMapPortal& _Other) = delete;
	MiniMapPortal(MiniMapPortal&& _Other) noexcept = delete;
	MiniMapPortal& operator=(const MiniMapPortal& _Other) = delete;
	MiniMapPortal& operator=(MiniMapPortal&& _Other) noexcept = delete;

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

protected:

private:

	float4 Destination = float4::ZERO;

	std::shared_ptr<GameEngineSpriteRenderer> PortalRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PortalCollision = nullptr;

	void Start() override;
	// void Update(float _Delta) override;
};