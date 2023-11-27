#pragma once

class LogoActor : public GameEngineActor
{
public:
	// constrcuter destructer
	LogoActor();
	~LogoActor();

	// delete Function
	LogoActor(const LogoActor& _Other) = delete;
	LogoActor(LogoActor&& _Other) noexcept = delete;
	LogoActor& operator=(const LogoActor& _Other) = delete;
	LogoActor& operator=(LogoActor&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineUIRenderer> LogoRenderer = nullptr;
};