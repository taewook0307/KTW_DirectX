#pragma once

class UpperObject : public GameEngineActor
{
public:
	// constrcuter destructer
	UpperObject();
	~UpperObject();

	// delete Function
	UpperObject(const UpperObject& _Other) = delete;
	UpperObject(UpperObject&& _Other) noexcept = delete;
	UpperObject& operator=(const UpperObject& _Other) = delete;
	UpperObject& operator=(UpperObject&& _Other) noexcept = delete;

	void UpperObjectInit(std::string_view _FileName, int _Order = 0, bool _WinSizeOn = true);
protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer>  UpperObjectRenderer = nullptr;

	void Start() override;
	void Update(float _Delta);
};