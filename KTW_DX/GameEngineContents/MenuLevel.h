#pragma once

#include "BaseLevel.h"

class MenuLevel : public BaseLevel
{
public:
	// constrcuter destructer
	MenuLevel();
	~MenuLevel();

	// delete Function
	MenuLevel(const MenuLevel& _Other) = delete;
	MenuLevel(MenuLevel&& _Other) noexcept = delete;
	MenuLevel& operator=(const MenuLevel& _Other) = delete;
	MenuLevel& operator=(MenuLevel&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class BackGround> Back = nullptr;

	std::shared_ptr<class SelectMenu> StartMenu = nullptr;
	std::shared_ptr<class SelectMenu> ExitMenu = nullptr;
	std::shared_ptr<class FadePostEffect> FadeEffect = nullptr;

	EMAINMENUSELECT CurSelect = EMAINMENUSELECT::Start;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;

	void MenuChange();

	bool IsFade = false;
	float LevelChangeTimer = 3.0f;
};