#include "PreCompile.h"
#include "MiniMapCharacter.h"

MiniMapCharacter::MiniMapCharacter()
{
}

MiniMapCharacter::~MiniMapCharacter()
{
}

void MiniMapCharacter::Start()
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\Texture\\Character");

	GameEngineFile File = Path.PlusFilePath("MiniMap_Character.png");

	GameEngineTexture::Load(File.GetStringPath());

	GameEngineSprite::CreateCut("MiniMap_Character.png", 10, 11);

	MainSprite = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::Play));
	MainSprite->CreateAnimation("MiniCharacter_Idle", "MiniMap_Character.png", 0.1f, 67, 70);
	MainSprite->ChangeAnimation("MiniCharacter_Idle");
	MainSprite->AutoSpriteSizeOn();
}

void MiniMapCharacter::Update(float _Delta)
{
	float Speed = 300.0f;

	if (GameEngineInput::IsPress(VK_UP))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress(VK_DOWN))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress(VK_RIGHT))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
}