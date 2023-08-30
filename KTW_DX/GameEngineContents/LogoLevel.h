#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class LogoLevel : public GameEngineLevel
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
	int Order = 0;

	std::shared_ptr<class BackGround> Logo;

	void Start() override;

	void Update(float _Delta) override;
};