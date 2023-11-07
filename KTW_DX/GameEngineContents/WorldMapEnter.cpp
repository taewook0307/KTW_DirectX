#include "PreCompile.h"
#include "WorldMapEnter.h"

WorldMapEnter::WorldMapEnter()
{
	GameEngineInput::AddInputObject(this);
}

WorldMapEnter::~WorldMapEnter()
{
}

void WorldMapEnter::Start()
{
	WorldMapEnterRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
	WorldMapEnterCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::FieldEnter);
}

void WorldMapEnter::Update(float _Delta)
{
	if (true == WorldMapEnterCollision->Collision(ECOLLISIONORDER::Player))
	{
		if (true == GameEngineInput::IsDown('Z', this) || true == GameEngineInput::IsDown(VK_RETURN, this))
		{
			GameEngineCore::ChangeLevel(EnterLevel);
		}
	}
}

void WorldMapEnter::EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName)
{
	WorldMapEnterRenderer->CreateAnimation(_AnimationName, _SpriteName);
	WorldMapEnterRenderer->ChangeAnimation(_AnimationName);
	WorldMapEnterRenderer->AutoSpriteSizeOn();
	WorldMapEnterRenderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineSprite> CurSprite = GameEngineSprite::Find(_SpriteName);
	float4 SpriteScale = CurSprite->GetSpriteData(0).GetScale();

	WorldMapEnterCollision->Transform.SetLocalScale(SpriteScale);
}

void WorldMapEnter::EnterSpriteInit(std::string_view _FileName, int _Order /*= 0*/)
{
	WorldMapEnterRenderer->SetSprite(_FileName, _Order);
	WorldMapEnterRenderer->AutoSpriteSizeOn();
	WorldMapEnterRenderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineSprite> CurSprite = GameEngineSprite::Find(_FileName);
	float4 SpriteScale = CurSprite->GetSpriteData(_Order).GetScale();

	WorldMapEnterCollision->Transform.SetLocalScale(SpriteScale);
}

void WorldMapEnter::SetCollisionScaleAndPosition(float4 _Scale /*= float4::ONE*/, float4 _Position /*= float4::ZERO*/)
{
	WorldMapEnterCollision->Transform.SetLocalScale(_Scale);
	WorldMapEnterCollision->Transform.SetLocalPosition(_Position);
}