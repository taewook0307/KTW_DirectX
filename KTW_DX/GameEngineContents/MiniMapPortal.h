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

protected:

private:
	void SetDestination(std::shared_ptr<MiniMapPortal> _Destination)
	{
		Destination = _Destination;
	}

	std::shared_ptr<MiniMapPortal> Destination = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> PortalRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PortalCollision = nullptr;

	void Start() override;
	// void Update(float _Delta) override;
};