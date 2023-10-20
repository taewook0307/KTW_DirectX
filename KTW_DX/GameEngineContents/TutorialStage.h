#pragma once

#define PLAYERSTARTPOS { 230.0f, - 605.0f }
#define TARGETPOS { 3565.0f, -350.f }
#define PARRYPOS1 { 3890.0f, -320.f }
#define PARRYPOS2 { 4090.0f, -320.f }
#define PARRYPOS3 { 4290.0f, -320.f }
#define EXITPOS { 6645.0f, -604.0f }

#include "StageLevel.h"

class TutorialStage : public StageLevel
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

private:
	std::shared_ptr<class BackGround> TutorialBackGround = nullptr;
	std::shared_ptr<class UpperObject> TutorialBackGroundUpper = nullptr;
	std::shared_ptr<class Map> TutorialMap = nullptr;
	std::shared_ptr<class TutorialTarget> Target = nullptr;
	std::shared_ptr<class MiniMapEnter> TutorialExit = nullptr;

	std::vector<std::shared_ptr<class ParryObject>> TutorialParry;

	void TutorialParryObjectActive();
	void TutorialLevelCameraMove();

private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;
};