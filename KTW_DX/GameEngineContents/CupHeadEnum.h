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
	None,
	BackGround,
	Map,
	Boss,
	Play,
	PlayEffect,
	MapUpper,
	Bullet,
	Fade,
	UI,
	Max
};

enum class ECOLLISIONORDER
{
	None,
	Player,
	Bullet,
	MonsterBody,
	MonsterAttack,
	UnDamageMonster,
	FieldEnter,
	ParryObject,
	Max
};