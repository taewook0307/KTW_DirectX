#pragma once

class HpMarker : public GameEngineActor
{
public:
	// constrcuter destructer
	HpMarker();
	~HpMarker();

	// delete Function
	HpMarker(const HpMarker& _Other) = delete;
	HpMarker(HpMarker&& _Other) noexcept = delete;
	HpMarker& operator=(const HpMarker& _Other) = delete;
	HpMarker& operator=(HpMarker&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> HpRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void HpCheck(int _Hp);
};