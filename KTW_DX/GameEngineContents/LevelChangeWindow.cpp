#include "PreCompile.h"
#include "LevelChangeWindow.h"

LevelChangeWindow::LevelChangeWindow()
{
}

LevelChangeWindow::~LevelChangeWindow()
{
}

void LevelChangeWindow::Start()
{

}

void LevelChangeWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::map<std::string, std::shared_ptr<GameEngineLevel>> Levels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> CurLevel : Levels)
	{
		CreateLevelButton(CurLevel.first.c_str());
	}
}

void LevelChangeWindow::CreateLevelButton(std::string_view _LevelName)
{
	std::string LevelName = _LevelName.data();

	if (ImGui::Button(LevelName.c_str()))
	{
		GameEngineCore::ChangeLevel(LevelName.c_str());
	}
}