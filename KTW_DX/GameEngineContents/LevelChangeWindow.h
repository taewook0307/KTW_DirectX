#pragma once

class LevelChangeWindow : public GameEngineGUIWindow
{
public:
	//// constrcuter destructer
	LevelChangeWindow();
	~LevelChangeWindow();

	// delete Function
	LevelChangeWindow(const LevelChangeWindow& _Other) = delete;
	LevelChangeWindow(LevelChangeWindow&& _Other) noexcept = delete;
	LevelChangeWindow& operator=(const LevelChangeWindow& _Other) = delete;
	LevelChangeWindow& operator=(LevelChangeWindow&& _Other) noexcept = delete;

	void CreateLevelButton(std::string_view _LevelName);

	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

protected:

private:
	std::vector<std::string> UILevelNames;
	std::vector<std::string> StageLevelNames;
};