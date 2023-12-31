enum class EUPDATEORDER
{
	UI,
	Player,
	Bullet,
	Monster,
	Effect,
	Map,
	Menu,
	BackGround
};

enum class ERENDERORDER
{
	BackGround,
	UpperBackGround,

	PrevMap,
	PrevMap1,
	PrevMap2,
	PrevMap3,
	PrevMap4,
	PrevMap5,
	Map,
	UpperMap,
	UpperMap1,
	UpperMap2,
	UpperMap3,
	UpperMap4,
	UpperMap5,

	PrevBoss,
	PrevBoss1,
	PrevBoss2,
	PrevBoss3,
	PrevBoss4,
	PrevBoss5,
	Boss,
	UpperBoss,
	UpperBoss1,
	UpperBoss2,
	UpperBoss3,
	UpperBoss4,
	UpperBoss5,

	BossEffect,
	
	BackEffect,
	Play,
	PlayEffect,
	
	UpperPlayer,
	UpperPlayer1,

	Bullet,
	UI,
	Max
};

enum class ECOLLISIONORDER
{
	None,
	Player,
	Bullet,
	BossBody,
	BossAttack,
	UnDamageBoss,
	MonsterBody,
	FieldEnter,
	ParryObject,
	Obstacle,
	TutorialTarget,
	Portal,
	Trigger,
	Max
};