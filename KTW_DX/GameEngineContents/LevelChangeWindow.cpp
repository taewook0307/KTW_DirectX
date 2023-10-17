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
	CreateLevelButton("LogoLevel");
	CreateLevelButton("TitleLevel");
	CreateLevelButton("MenuLevel");
	CreateLevelButton("IntroLevel");
	CreateLevelButton("MiniMapLevel");
	CreateLevelButton("TutorialStage");
	CreateLevelButton("FirstBossStage");
	CreateLevelButton("SecondBossStage");
	CreateLevelButton("OutroLevel");
}

void LevelChangeWindow::CreateLevelButton(std::string_view _LevelName)
{
	std::string LevelName = _LevelName.data();

	if (ImGui::Button(LevelName.c_str()))
	{
		GameEngineCore::ChangeLevel(LevelName.c_str());
	}
}