#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class TutorialStage : public GameEngineLevel
{
public:
	// constrcuter destructer
	TutorialStage();
	~TutorialStage();

	// delete Function
	TutorialStage(const TutorialStage& _Other) = delete;
	TutorialStage(TutorialStage&& _Other) noexcept = delete;
	TutorialStage& operator=(const TutorialStage& _Other) = delete;
	TutorialStage& operator=(TutorialStage&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class BackGround> TutorialBackGround = nullptr;
	std::shared_ptr<class UpperObject> TutorialBackGroundUpper = nullptr;
	std::shared_ptr<class Map> TutorialMap = nullptr;
	std::shared_ptr<class BaseCharacter> Player = nullptr;

	void TutorialLevelCameraMove();
};