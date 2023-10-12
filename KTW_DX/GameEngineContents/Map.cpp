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
	GameEngineInput::AddInputObject(this);
	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
	PixelMapRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
}

void Map::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J', this))
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
		MapRenderer->SetImageScale(GameEngineCore::MainWindow.GetScale());
	}
	else
	{
		MapRenderer->AutoSpriteSizeOn();
	}
}

void Map::PixelMapInit(std::string_view _SpriteName)
{
	PixelMapRenderer->SetSprite(_SpriteName);
	PixelMapRenderer->AutoSpriteSizeOn();

	PixelMapFileName = _SpriteName;

	PixelMapRenderer->Off();
}

GameEngineColor Map::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(PixelMapFileName);

	return Tex->GetColor(_Pos, _DefaultColor);
}

void Map::RendererSwitch()
{
	PixelMapRenderSwitch = !PixelMapRenderSwitch;

	if (true == PixelMapRenderSwitch)
	{
		MapRenderer->Off();
		PixelMapRenderer->On();
	}
	else
	{
		MapRenderer->On();
		PixelMapRenderer->Off();
	}
}