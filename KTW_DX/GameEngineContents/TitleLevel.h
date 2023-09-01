#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;

private:
	std::shared_ptr<class BackGround> TitleBackGround = nullptr;
	std::shared_ptr<class BackGround> TitleAnimation = nullptr;
};