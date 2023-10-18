#include "PreCompile.h"
#include "LevelChangeWindow.h"

//LevelChangeWindow::LevelChangeWindow()
//{
//}
//
//LevelChangeWindow::~LevelChangeWindow()
//{
//}

void LevelChangeWindow::Start()
{

}

void LevelChangeWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Text("Debug");
	if (ImGui::Button("Collision Switch"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	ImGui::Text("UI");

	CreateLevelButton("LogoLevel");
	CreateLevelButton("TitleLevel");
	CreateLevelButton("MenuLevel");
	CreateLevelButton("IntroLevel");
	CreateLevelButton("OutroLevel");

	ImGui::Text("Stage");

	CreateLevelButton("MiniMapLevel");
	CreateLevelButton("TutorialStage");
	CreateLevelButton("FirstBossStage");
	CreateLevelButton("SecondBossStage");
}

void LevelChangeWindow::CreateLevelButton(std::string_view _LevelName)
{
	std::string LevelName = _LevelName.data();

	if (ImGui::Button(LevelName.c_str()))
	{
		GameEngineCore::ChangeLevel(LevelName.c_str());
	}
}