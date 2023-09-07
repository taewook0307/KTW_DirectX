enum class UpdateOrder
{
	UI,
	Player,
	Bullet,
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
	Bullet,
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