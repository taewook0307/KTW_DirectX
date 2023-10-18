#include "PreCompile.h"
#include "DebugWindow.h"

#include "BaseCharacter.h"

DebugWindow::DebugWindow()
{
}

DebugWindow::~DebugWindow()
{
}

void DebugWindow::Start()
{

}

void DebugWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Text("Debug");

	if (ImGui::Button("Collision Switch"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	std::string IsCheat = "Cheat : ";

	if (true == BaseCharacter::MainCharacter->GetCheat())
	{
		IsCheat += "On";
	}
	else
	{
		IsCheat += "Off";
	}

	ImGui::Text(IsCheat.c_str());

	if (ImGui::Button("Cheat Switch"))
	{
		BaseCharacter::MainCharacter->CheatSwitch();
	}
}