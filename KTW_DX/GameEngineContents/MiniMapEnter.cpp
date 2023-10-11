#include "PreCompile.h"
#include "MiniMapEnter.h"

MiniMapEnter::MiniMapEnter()
{
}

MiniMapEnter::~MiniMapEnter()
{
}

void MiniMapEnter::Start()
{
	MiniMapEnterRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
	MiniMapEnterCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::FieldEnter);
}

void MiniMapEnter::Update(float _Delta)
{
	if (true == MiniMapEnterCollision->Collision(ECOLLISIONORDER::Player))
	{
		if (true == GameEngineInput::IsDown('Z') || true == GameEngineInput::IsDown(VK_RETURN))
		{
			GameEngineCore::ChangeLevel(EnterLevel);
		}
	}
}

void MiniMapEnter::EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName)
{
	MiniMapEnterRenderer->CreateAnimation(_AnimationName, _SpriteName);
	MiniMapEnterRenderer->ChangeAnimation(_AnimationName);
	MiniMapEnterRenderer->AutoSpriteSizeOn();
	MiniMapEnterRenderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineSprite> CurSprite = GameEngineSprite::Find(_SpriteName);
	float4 SpriteScale = CurSprite->GetSpriteData(0).GetScale();

	MiniMapEnterCollision->Transform.SetLocalScale(SpriteScale);
}

void MiniMapEnter::EnterSpriteInit(std::string_view _FileName, int _Order /*= 0*/)
{
	MiniMapEnterRenderer->SetSprite(_FileName, _Order);
	MiniMapEnterRenderer->AutoSpriteSizeOn();
	MiniMapEnterRenderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineSprite> CurSprite = GameEngineSprite::Find(_FileName);
	float4 SpriteScale = CurSprite->GetSpriteData(_Order).GetScale();

	MiniMapEnterCollision->Transform.SetLocalScale(SpriteScale);
}

void MiniMapEnter::SetCollisionScaleAndPosition(float4 _Scale /*= float4::ONE*/, float4 _Position /*= float4::ZERO*/)
{
	MiniMapEnterCollision->Transform.SetLocalScale(_Scale);
	MiniMapEnterCollision->Transform.SetLocalPosition(_Position);
}