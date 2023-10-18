#pragma once

#include <GameEngineCore/GameEngineGUI.h>

class DebugWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	DebugWindow();
	~DebugWindow();

	// delete Function
	DebugWindow(const DebugWindow& _Other) = delete;
	DebugWindow(DebugWindow&& _Other) noexcept = delete;
	DebugWindow& operator=(const DebugWindow& _Other) = delete;
	DebugWindow& operator=(DebugWindow&& _Other) noexcept = delete;

	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

protected:

private:
	
};