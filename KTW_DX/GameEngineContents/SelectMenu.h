#pragma once

class SelectMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectMenu();
	~SelectMenu();

	// delete Function
	SelectMenu(const SelectMenu& _Other) = delete;
	SelectMenu(SelectMenu&& _Other) noexcept = delete;
	SelectMenu& operator=(const SelectMenu& _Other) = delete;
	SelectMenu& operator=(SelectMenu&& _Other) noexcept = delete;

	inline void SelectOn()
	{
		IsSelect = true;
	}

	inline void SelectOff()
	{
		IsSelect = false;
	}

	void SelectMenuInit(std::string_view _SelectFileName, std::string_view _UnSelectFileName);

	void OnRendererInit(std::string_view _FileName, int _Order = 0);
	
	void OffRendererInit(std::string_view _FileName, int _Order = 0);

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> OnRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> OffRenderer = nullptr;

	bool IsSelect = false;

	void Start() override;
	void Update(float _Delta) override;
};