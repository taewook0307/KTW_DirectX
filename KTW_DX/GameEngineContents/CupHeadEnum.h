enum class UpdateOrder
{
	UI,
	Player,
	Monster,
	Map,
	Menu,
	BackGround
};

enum class RenderOrder
{
	None,
	BackGround,
	Map,
	Play,
	MapUpper,
	Fade,
	UI,
	Max
};

enum class CollisionOrder
{
	None,
	Player,
	Bullet,
	Monster,
	FieldEnter,
	Max
};