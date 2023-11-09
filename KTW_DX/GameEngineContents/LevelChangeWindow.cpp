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
	UILevelNames.reserve(5);
	StageLevelNames.reserve(5);

	std::map<std::string, std::shared_ptr<GameEngineLevel>> Levels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> CurLevel : Levels)
	{
		std::string LevelName = CurLevel.first.c_str();

		if (std::string::npos == LevelName.find("_STAGE"))
		{
			UILevelNames.push_back(LevelName);
		}
		else
		{
			StageLevelNames.push_back(LevelName);
		}
	}
}

void LevelChangeWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::map<std::string, std::shared_ptr<GameEngineLevel>> Levels = GameEngineCore::GetAllLevel();

	ImGui::Text("etc");

	for (size_t i = 0; i < UILevelNames.size(); i++)
	{
		CreateLevelButton(UILevelNames[i]);
	}

	ImGui::Text("Stage");

	for (size_t i = 0; i < StageLevelNames.size(); i++)
	{
		CreateLevelButton(StageLevelNames[i]);
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