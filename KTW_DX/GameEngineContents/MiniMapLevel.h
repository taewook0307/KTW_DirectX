#pragma once

#define TUTORIALENTERPOS { 800.0f, -2200.0f }
#define TUTORIALENTERCOLLISIONSCALE { 270.0f, 240.0f }
#define TUTORIALENTERCOLLISIONSPOSITION { 0.0f, 240.0f }

#define FIRSTBOSSENTERPOS { 2205.0f, -2070.0f }
#define FIRSTBOSSENTERCOLLISIONSCALE { 230.0f, 200.0f }
#define FIRSTBOSSENTERCOLLISIONSPOSITION { 0.0f, 100.0f }

#define SECONDBOSSENTERPOS { 4100.0f, -2620.0f }
#define SECONDBOSSENTERCOLLISIONSCALE { 460.0f, 540.0f }

#define CHARACTERSTARTPOS { 885.0f, -2208.0f }

#define FIRSTFLAGPOSITION { 2225.0f, -2130.0f }
#define SECONDFLAGPOSITION { 3840.0f, -2570.0f }

#define ISLANDPORTALPOS { 3700.0f, -2100.0f }
#define DEVILISLANDPORTALPOS { 5110.0f, -1260.0f }

#define LASTBOSSENTERSCALE { 50.0f, 50.0f }
#define LASTBOSSENTERPOSITION { 5750.0f, -600.0f }

class MiniMapLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MiniMapLevel();
	~MiniMapLevel();

	// delete Function
	MiniMapLevel(const MiniMapLevel& _Other) = delete;
	MiniMapLevel(MiniMapLevel&& _Other) noexcept = delete;
	MiniMapLevel& operator=(const MiniMapLevel& _Other) = delete;
	MiniMapLevel& operator=(MiniMapLevel&& _Other) noexcept = delete;

	static void IsCreateStage1Flag()
	{
		CreateStage1Flag = true;
	}

	static void IsCreateStage2Flag()
	{
		CreateStage2Flag = true;
	}

protected:

private:
	float4 MapScale = float4::ZERO;
	float4 CalCameraPos(const float4& _SetPos);

	std::shared_ptr<class Map> MiniMap = nullptr;
	std::shared_ptr<class UpperObject> MiniMapUpper = nullptr;
	std::shared_ptr<class MiniMapCharacter> Character = nullptr;

	std::shared_ptr<class MiniMapEnter> TutorialEnter = nullptr;
	std::shared_ptr<class MiniMapEnter> FirstBossEnter = nullptr;
	std::shared_ptr<class MiniMapEnter> SecondBossEnter = nullptr;
	std::shared_ptr<class Trigger> LastBossEnter = nullptr;

	std::shared_ptr<class MiniMapFlag> FirstBossFlag = nullptr;
	std::shared_ptr<class MiniMapFlag> SecondBossFlag = nullptr;

	std::shared_ptr<class MiniMapPortal> IslandPortal = nullptr;
	std::shared_ptr<class MiniMapPortal> DevilIslandPortal = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;

	static float4 CharacterSavePos;
	static bool Stage1Clear;
	static bool Stage2Clear;

	static bool CreateStage1Flag;
	static bool CreateStage2Flag;

	static bool PortalSpawnDone;
	float CameraMoveSpeed = 500.0f;
	bool IslandPortalAnimationEndCheck();
	void IslandPortalSpawn(float _Delta);

	bool DevilIslandPortalAnimationEndCheck();
	void DevilIslandPortalSpawn(float _Delta);

	bool CameraMoveToCharacterPos(float _Delta);

	GameEngineState MiniMapState;
};