#pragma once

#include "BaseLevel.h"

class TitleLevel : public BaseLevel
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

private:
	std::shared_ptr<class BackGround> TitleBackGround = nullptr;
	std::shared_ptr<class BackGround> TitleAnimation = nullptr;
	std::shared_ptr<class FadeObject> FadeEffect = nullptr;

	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};