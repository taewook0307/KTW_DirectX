#include "PreCompile.h"
#include "DebugWindow.h"

#include "BaseCharacter.h"
#include "Map.h"

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

	if (ImGui::Button("Map Switch"))
	{
		if (nullptr != Map::MainMap)
		{
			Map::MainMap->RendererSwitch();
		}
		
	}

	if (ImGui::Button("Cheat Switch"))
	{
		if (nullptr != BaseCharacter::MainCharacter)
		{
			BaseCharacter::MainCharacter->CheatSwitch();
		}
	}
}