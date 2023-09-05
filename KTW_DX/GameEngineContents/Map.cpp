#include "PreCompile.h"
#include "Map.h"

Map* Map::MainMap = nullptr;

Map::Map()
{
	MainMap = this;
}

Map::~Map()
{
}

void Map::Start()
{
	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Map);
	BitMapRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Map);
}

void Map::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		RendererSwitch();
	}
}

void Map::MapInit(std::string_view _SpriteName)
{
	MapRenderer->SetSprite(_SpriteName);
	MapRenderer->AutoSpriteSizeOn();
}

void Map::MapAnimationInit(std::string_view _AnimationName, std::string_view _FileName, float _Inter /*= 0.1f*/, bool _Loop /*= true*/, bool _SizeFixWindow /*= true*/, unsigned int _Start /*= -1*/, unsigned int _End /*= -1*/)
{
	MapRenderer->CreateAnimation(_AnimationName, _FileName, _Inter, _Start, _End, _Loop);
	MapRenderer->ChangeAnimation(_AnimationName);

	if (true == _SizeFixWindow)
	{
		MapRenderer->Transform.SetLocalScale(GameEngineCore::MainWindow.GetScale());
	}
	else
	{
		MapRenderer->AutoSpriteSizeOn();
	}
}

void Map::BitMapInit(std::string_view _SpriteName)
{
	BitMapRenderer->SetSprite(_SpriteName);
	BitMapRenderer->AutoSpriteSizeOn();

	BitMapFileName = _SpriteName;

	BitMapRenderer->Off();
}

GameEngineColor Map::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(BitMapFileName);

	return Tex->GetColor(_Pos, _DefaultColor);
}

void Map::RendererSwitch()
{
	BitMapRenderSwitch = !BitMapRenderSwitch;

	if (true == BitMapRenderSwitch)
	{
		MapRenderer->Off();
		BitMapRenderer->On();
	}
	else
	{
		MapRenderer->On();
		BitMapRenderer->Off();
	}
}