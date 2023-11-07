#pragma once

#include "BaseLevel.h"

class LogoLevel : public BaseLevel
{
public:
	// constrcuter destructer
	LogoLevel();
	~LogoLevel();

	// delete Function
	LogoLevel(const LogoLevel& _Other) = delete;
	LogoLevel(LogoLevel&& _Other) noexcept = delete;
	LogoLevel& operator=(const LogoLevel& _Other) = delete;
	LogoLevel& operator=(LogoLevel&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class BackGround> Logo = nullptr;

	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};