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
	EnterRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
	EnterCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::FieldEnter);
}

void MiniMapEnter::Update(float _Delta)
{
	if (true == EnterCollision->Collision(ECOLLISIONORDER::Player))
	{
		if (true == GameEngineInput::IsDown('Z') || true == GameEngineInput::IsDown(VK_RETURN))
		{
			GameEngineCore::ChangeLevel(EnterLevel);
		}
	}
}

void MiniMapEnter::EnterAnimationInit(std::string_view _AnimationName, std::string_view _SpriteName)
{
	EnterRenderer->CreateAnimation(_AnimationName, _SpriteName);
	EnterRenderer->ChangeAnimation(_AnimationName);
	EnterRenderer->AutoSpriteSizeOn();
	EnterRenderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineSprite> CurSprite = GameEngineSprite::Find(_SpriteName);
	float4 SpriteScale = CurSprite->GetSpriteData(0).GetScale();

	EnterCollision->Transform.SetLocalScale(SpriteScale);
}

void MiniMapEnter::EnterSpriteInit(std::string_view _FileName, int _Order /*= 0*/)
{
	EnterRenderer->SetSprite(_FileName, _Order);
	EnterRenderer->AutoSpriteSizeOn();
	EnterRenderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineSprite> CurSprite = GameEngineSprite::Find(_FileName);
	float4 SpriteScale = CurSprite->GetSpriteData(_Order).GetScale();

	EnterCollision->Transform.SetLocalScale(SpriteScale);
}